//
//  CDASingleFisheyeController.m
//  DORAMediaKit-iOSDemo
//
//  Created by wuping on 23/11/2017.
//  Copyright © 2017 DORAPlayer. All rights reserved.
//

#import "CDASingleFisheyeController.h"
#import <DORAMediaFramework/DORAMediaFramework.h>
#import "AppConstant.h"

@interface CDASingleFisheyeController ()

@property (nonatomic, strong) DORAPlayer *player;
@property (nonatomic, weak) UIView *displayView;
@property (nonatomic, weak) UIButton *playBtn;

@property (nonatomic, assign) DORAPanoPerspectiveMode currentPanoMode;

@end

@implementation CDASingleFisheyeController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"单鱼眼";
    [self setupViews];
}

- (void)setupViews
{
    self.view.backgroundColor = [UIColor whiteColor];
    
    UIView *displayView = [[UIView alloc] initWithFrame:CGRectMake(0, 30, kScreenWidth, kScreenWidth)];
    displayView.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:displayView];
    self.displayView = displayView;
    
    UIButton *actionBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    actionBtn.frame = CGRectMake(10, self.view.bounds.size.height - 240, kScreenWidth - 20, 50);
    [actionBtn setTitle:@"开始播放" forState:UIControlStateNormal];
    [actionBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    actionBtn.layer.cornerRadius = 5.0;
    actionBtn.clipsToBounds = YES;
    [actionBtn setBackgroundColor:[UIColor colorWithRed:50/255.0 green:64/255.0 blue:87/255.0 alpha:0.8/1.0]];
    [actionBtn addTarget:self action:@selector(startPlayer) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:actionBtn];
    
    UIButton *playBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    playBtn.frame = CGRectMake(10, self.view.bounds.size.height - 180, kScreenWidth - 20, 50);
    [playBtn setTitle:@"暂停" forState:UIControlStateNormal];
    [playBtn setTitle:@"继续" forState:UIControlStateSelected];
    playBtn.layer.cornerRadius = 5.0;
    playBtn.clipsToBounds = YES;
    [playBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [playBtn setBackgroundColor:[UIColor colorWithRed:50/255.0 green:64/255.0 blue:87/255.0 alpha:0.8/1.0]];
    [playBtn addTarget:self action:@selector(playOrPauseRtspPlayer:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:playBtn];
    self.playBtn = playBtn;
    
    UIButton *panoModeBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    panoModeBtn.frame = CGRectMake(10, self.view.bounds.size.height - 120, kScreenWidth - 20, 50);
    panoModeBtn.layer.cornerRadius = 5.0;
    panoModeBtn.clipsToBounds = YES;
    [panoModeBtn setTitle:@"鱼眼" forState:UIControlStateNormal];
    [panoModeBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [panoModeBtn setBackgroundColor:[UIColor colorWithRed:50/255.0 green:64/255.0 blue:87/255.0 alpha:0.8/1.0]];
    [panoModeBtn addTarget:self action:@selector(panoModeBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:panoModeBtn];
    
    UIButton *mountBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    mountBtn.frame = CGRectMake(10, self.view.bounds.size.height - 60, kScreenWidth - 20, 50);
    mountBtn.layer.cornerRadius = 5.0;
    mountBtn.clipsToBounds = YES;
    [mountBtn setTitle:@"Desktop Mount" forState:UIControlStateNormal];
    [mountBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [mountBtn setBackgroundColor:[UIColor colorWithRed:50/255.0 green:64/255.0 blue:87/255.0 alpha:0.8/1.0]];
    [mountBtn addTarget:self action:@selector(setMountMode:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:mountBtn];
}

- (void)panoModeBtnClicked:(UIButton *)sender
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

- (void)setMountMode:(UIButton *)sender
{
    static int i = 0;
    i++;
    [self.player changeMountMode:i % 3];
    
    switch (i % 3) {
        case 0:
            [sender setTitle:@"Desktop Mount" forState:UIControlStateNormal];
            break;
        case 1:
            [sender setTitle:@"Wall Mount" forState:UIControlStateNormal];
            break;
        case 2:
            [sender setTitle:@"Ceiling Mount" forState:UIControlStateNormal];
            break;
            
        default:
            break;
    }
}

- (void)initPlayer
{
    NSString *rtspStr = @"http://camsgear-demo-resource.oss-cn-hangzhou.aliyuncs.com/mono_fisheye.jpg";
    
    DORAFFOptions *options = [DORAFFOptions optionsByDefault];

    DORAPlayer *player = [DORAPlayer sharedPlayer];
    self.player = player;
    
    int height = 1080;
    int width = 1920;
    NSString *calibrationData = [NSString stringWithFormat:@"version=v1&type=1&data=%f,0.5,0.5,1.570796326794896619231322,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000;0.495394,1.511058,0.502757,1.753863,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000;0.602270,0.874488,0.940670,0.969515,0.526458,0.627032,0.961586,0.904201,0.206726,0.508845,0.352884,0.560779,0.411990,0.498598,0.070204,0.821680;0.733293,0.050407,0.425355,0.921722,0.777676,0.640256,0.133516,0.093034,0.530997,0.503261,0.269104,0.748532,0.495609,0.128849,0.832392,0.516214", (float)width / 2.0f / (float)height];
    
    NSDictionary *mediaInfo = @{
                                @"count" : @"1",
//                                @"fov" : @"210",
//                                @"fps" : @"30",
//                                @"height" : @"1080",
//                                @"mount" : @"1",
//                                @"needStitch" : @"1",
//                                @"order" : @"2",
//                                @"orientation" : @"0",
                                @"projection" : @"0",
//                                @"width" : @"1080"
                                };
    
    [player setContentURLString:rtspStr withOptions:options withPlayerSize:CGSizeMake(kScreenWidth, kScreenWidth) withMediaInfo:mediaInfo withCalibrationData:calibrationData];
    
    [player addGestureTo:self.displayView];
    [self.displayView addSubview:player.displayView];
}

- (void)startPlayer
{
    if (self.player == nil) {
        [self initPlayer];
        [self.player prepareToPlay];
    }
}

- (void)playOrPauseRtspPlayer:(UIButton *)sender
{
    if (sender.selected) {
        [self.player play];
    } else {
        [self.player pause];
    }
    sender.selected = !sender.selected;
}

- (void)releasePlayer
{
    [self.player shutdown];
    self.player = nil;
    self.playBtn.selected = NO;
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [self releasePlayer];
}


@end
