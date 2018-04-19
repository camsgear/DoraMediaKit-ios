//
//  CDASingleH264PlayerController.m
//  DORADemo
//
//  Created by wuping on 21/11/2017.
//  Copyright © 2017 DORAPlayer. All rights reserved.
//

#import "CDASingleH264PlayerController.h"
#import "LayerPixer.h"
#import "VideoFileParser.h"
#import <DORAMediaFramework/DORAMediaFramework.h>
#import "AppConstant.h"

@interface CDASingleH264PlayerController ()<PackSortDelegate>

@property (nonatomic, strong) DORAPlayer *player;
@property (nonatomic, strong) LayerPixer *layerPixer;

@property (nonatomic, weak) UIView *displayView;
@property (nonatomic, weak) UIButton *startBtn;
@property (nonatomic, weak) UIButton *stopBtn;

@property (nonatomic, assign) DORAPanoPerspectiveMode currentPanoMode;

@end

@implementation CDASingleH264PlayerController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"单帧H264播放";
    [self setupViews];
}

- (void)setupViews
{
    self.view.backgroundColor = [UIColor whiteColor];
    
    // display view
    UIView *displayView = [[UIView alloc] initWithFrame:CGRectMake(0, 64, kScreenWidth, kScreenWidth)];
    displayView.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:displayView];
    self.displayView = displayView;
    
    // action buttons
    UIButton *startBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    startBtn.frame = CGRectMake(10, self.view.bounds.size.height - 140, kScreenWidth / 2 - 20, 50);
    [startBtn setTitle:@"start" forState:UIControlStateNormal];
    startBtn.backgroundColor = [UIColor colorWithRed:50/255.0 green:64/255.0 blue:87/255.0 alpha:0.8/1.0];
    startBtn.layer.cornerRadius = 5.0;
    startBtn.clipsToBounds = YES;
    [startBtn addTarget:self action:@selector(startBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:startBtn];
    self.startBtn = startBtn;

    UIButton *stopBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    stopBtn.frame = CGRectMake(kScreenWidth / 2 + 10, kScreenHeight - 140, kScreenWidth / 2 - 20, 50);
    [stopBtn setTitle:@"stop" forState:UIControlStateNormal];
    stopBtn.backgroundColor = [UIColor colorWithRed:50/255.0 green:64/255.0 blue:87/255.0 alpha:0.8/1.0];
    stopBtn.layer.cornerRadius = 5.0;
    stopBtn.clipsToBounds = YES;
    [stopBtn addTarget:self action:@selector(stopBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:stopBtn];
    self.stopBtn = stopBtn;
    
    UIButton *modeBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    modeBtn.frame = CGRectMake(10, self.view.bounds.size.height - 70, kScreenWidth - 20, 50);
    modeBtn.layer.cornerRadius = 5.0;
    modeBtn.clipsToBounds = YES;
    [modeBtn setTitle:@"鱼眼" forState:UIControlStateNormal];
    [modeBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [modeBtn setBackgroundColor:[UIColor colorWithRed:50/255.0 green:64/255.0 blue:87/255.0 alpha:0.8/1.0]];
    [modeBtn addTarget:self action:@selector(setMode:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:modeBtn];
}

- (void)startBtnClicked:(UIButton *)btn
{
    if (btn.selected) {
        return;
    }
    btn.selected = !btn.selected;
    self.stopBtn.selected = NO;
    
    [self initSingleH264Player];
    [self performSelector:@selector(defaultH264Data) withObject:nil afterDelay:0.01];
}

- (void)stopBtnClicked:(UIButton *)btn
{
    if (btn.selected) {
        return;
    }
    btn.selected = !btn.selected;
    self.startBtn.selected = NO;
    
    [self singleH264PlayerShutdown];
    
    self.layerPixer.delegate = nil;
    self.layerPixer.closeFileParser = YES;
    self.layerPixer = nil;
}

- (void)setMode:(UIButton *)sender
{
    self.currentPanoMode = (++self.currentPanoMode) % 3;
    [self.player changePerspectiveMode:self.currentPanoMode];
    
    switch (self.currentPanoMode) {
        case DORAPanoPerspectiveModeFisheye:
            [sender setTitle:@"鱼眼" forState:UIControlStateNormal];
            break;
        case DORAPanoPerspectiveModeLittlePlanet:
            [sender setTitle:@"小行星" forState:UIControlStateNormal];
            break;
        case DORAPanoPerspectiveModeNormal:
            [sender setTitle:@"普通" forState:UIControlStateNormal];
            break;
            
        default:
            break;
    }
}

- (void)defaultH264Data
{
    self.layerPixer = [[LayerPixer alloc] init];
    self.layerPixer.closeFileParser = NO;
    self.layerPixer.delegate = self;
    [self.layerPixer decodeFile:@"l_split" fileExt:@"h264"];
}

- (void)sortPackData:(VideoPacket *)pack frameType:(FRAMETYPE)type
{
    //    if (type == FRAMETYPE_I) {
    [self.player inputSingleH264Data:pack.buffer length:pack.size];
    //    }
    
}

- (void)logByte:(uint8_t *)bytes Len:(int)len Str:(NSString *)str
{
    NSMutableString *tempMStr=[[NSMutableString alloc] init];
    for (int i=0;i<len;i++)
        [tempMStr appendFormat:@"%0x ",bytes[i]];
    NSLog(@"%@ == %@",str,tempMStr);
}


#pragma mark - H264裸流单帧播放
// 初始化裸流播放器
- (void)initSingleH264Player
{
    self.player = [DORAPlayer sharedPlayer];
    
    NSDictionary *mediaInfo = @{
//                                @"count" : @"1",
//                                @"fov" : @"210",
//                                @"fps" : @"30",
//                                @"height" : @"1080",
//                                @"mount" : @"0",
//                                @"needStitch" : @"1",
//                                @"order" : @"2",
//                                @"orientation" : @"0",
                                @"projection" : @"1",
//                                @"width" : @"1080"
                                };
    
    [self.player setSingleH264WithPlayerSize:CGSizeMake(kScreenWidth, kScreenWidth) withMediaInfo:mediaInfo withCalibrationData:nil];
    
    [self.player addGestureTo:self.displayView];
    
    // 添加单帧图片输出视图到self.view
    [self.displayView addSubview:self.player.displayView];
    self.player.displayView.backgroundColor = [UIColor lightGrayColor];
}

// 单帧H264数据播放
- (void)inputSingleH264Data:(uint8_t *)data length:(long)length
{
    [self.player inputSingleH264Data:data length:length];
}

// 单帧H264停止播放
- (void)singleH264PlayerShutdown
{
    [self.player singleH264PlayerShutdown];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [self singleH264PlayerShutdown];
    self.layerPixer.delegate = nil;
    self.layerPixer.closeFileParser = YES;
    self.layerPixer = nil;
}

- (void)dealloc
{
    NSLog(@"CDASingleH264PlayerController dealloc");
}

@end
