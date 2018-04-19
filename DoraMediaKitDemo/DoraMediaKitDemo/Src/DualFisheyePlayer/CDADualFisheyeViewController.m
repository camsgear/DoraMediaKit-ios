//
//  CDADualFisheyeViewController.m
//  DORAMediaKit-iOSDemo
//
//  Created by Edwin Cen on 04/12/2017.
//  Copyright © 2017 DORAPlayer. All rights reserved.
//

#import "CDADualFisheyeViewController.h"
#import <DORAMediaFramework/DORAMediaFramework.h>
#import "AppConstant.h"

@interface CDADualFisheyeViewController ()
@property (nonatomic, strong) DORAPlayer *player;
@property (nonatomic, weak) UIView *displayView;
@property (nonatomic, weak) UIButton *playBtn;
@property (nonatomic, assign) DORAPanoPerspectiveMode currentPanoMode;
@end

@implementation CDADualFisheyeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"双鱼眼";
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
    actionBtn.frame = CGRectMake(10, self.view.bounds.size.height - 180, kScreenWidth - 20, 50);
    [actionBtn setTitle:@"开始播放" forState:UIControlStateNormal];
    [actionBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    actionBtn.layer.cornerRadius = 5.0;
    actionBtn.clipsToBounds = YES;
    [actionBtn setBackgroundColor:[UIColor colorWithRed:50/255.0 green:64/255.0 blue:87/255.0 alpha:0.8/1.0]];
    [actionBtn addTarget:self action:@selector(startPlayer) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:actionBtn];
    
    UIButton *playBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    playBtn.frame = CGRectMake(10, self.view.bounds.size.height - 120, kScreenWidth - 20, 50);
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
    panoModeBtn.frame = CGRectMake(10, self.view.bounds.size.height - 60, (kScreenWidth - 40) / 3, 50);
    panoModeBtn.layer.cornerRadius = 5.0;
    panoModeBtn.clipsToBounds = YES;
    [panoModeBtn setTitle:@"鱼眼" forState:UIControlStateNormal];
    [panoModeBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [panoModeBtn setBackgroundColor:[UIColor colorWithRed:50/255.0 green:64/255.0 blue:87/255.0 alpha:0.8/1.0]];
    [panoModeBtn addTarget:self action:@selector(panoModeBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:panoModeBtn];
    
    UIButton *mountBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    mountBtn.frame = CGRectMake(20 + (kScreenWidth - 40) / 3, self.view.bounds.size.height - 60, (kScreenWidth - 40) / 3, 50);
    mountBtn.layer.cornerRadius = 5.0;
    mountBtn.clipsToBounds = YES;
    [mountBtn setTitle:@"平放" forState:UIControlStateNormal];
    [mountBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [mountBtn setBackgroundColor:[UIColor colorWithRed:50/255.0 green:64/255.0 blue:87/255.0 alpha:0.8/1.0]];
    [mountBtn addTarget:self action:@selector(setMountMode:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:mountBtn];
    
    UIButton *gyroscopeBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    gyroscopeBtn.frame = CGRectMake(30 + (kScreenWidth - 40) / 3 * 2, self.view.bounds.size.height - 60, (kScreenWidth - 40) / 3, 50);
    gyroscopeBtn.layer.cornerRadius = 5.0;
    gyroscopeBtn.clipsToBounds = YES;
    [gyroscopeBtn setTitle:@"打开陀螺仪" forState:UIControlStateNormal];
    [gyroscopeBtn setTitle:@"关闭陀螺仪" forState:UIControlStateSelected];
    [gyroscopeBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [gyroscopeBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateSelected];
    [gyroscopeBtn setBackgroundColor:[UIColor colorWithRed:50/255.0 green:64/255.0 blue:87/255.0 alpha:0.8/1.0]];
    [gyroscopeBtn addTarget:self action:@selector(setGyroscope:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:gyroscopeBtn];
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
            [sender setTitle:@"平放" forState:UIControlStateNormal];
            break;
        case 1:
            [sender setTitle:@"吊装" forState:UIControlStateNormal];
            break;
        case 2:
            [sender setTitle:@"壁挂" forState:UIControlStateNormal];
            break;
            
        default:
            break;
    }
}

- (void)setGyroscope:(UIButton *)sender
{
    [sender setSelected:!sender.isSelected];
    if (self.player) {
        [self.player setGyroActive:sender.isSelected];
    }
}

- (void)initPlayer
{
    NSString *mediaStr = @"http://camsgear-demo-resource.oss-cn-hangzhou.aliyuncs.com/dual_fisheye.mp4";
    
    DORAFFOptions *options = [DORAFFOptions optionsByDefault];
    
    DORAPlayer *player = [DORAPlayer sharedPlayer];
    self.player = player;
    NSString *calibrationData = @"version=v1&type=1&data=0.488039,0.511702,0.496324,1.715383,2.000000,0.068213,0.068160,0.997674,1.000000,-0.032618,-0.032612,0.999468,3.000000,0.009660,0.009660,0.999953;0.510947,1.51262,0.492647,1.747215,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000;0.775027,0.407191,0.667582,0.279639,0.437965,0.482050,0.613218,0.799896,0.642609,0.381717,0.828006,0.445646,0.010479,0.271403,0.110786,0.144212;0.549274,0.733412,0.822921,0.572398,0.816437,0.632281,0.299005,0.336998,0.846740,0.024951,0.835077,0.996719,0.645297,0.207707,0.167638,0.777443";
    
    NSDictionary *mediaInfo = @{
                                @"count" : @"2",
                                //                                @"fov" : @"210",
                                //                                @"fps" : @"30",
                                //                                @"height" : @"1080",
                                //                                @"mount" : @"1",
                                @"needStitch" : @"1",
                                //                                @"order" : @"2",
                                //                                @"orientation" : @"0",
                                @"projection" : @"0",
                                //                                @"width" : @"1080"
                                };
    
    [player setContentURLString:mediaStr withOptions:options withPlayerSize:CGSizeMake(kScreenWidth, kScreenWidth) withMediaInfo:mediaInfo withCalibrationData:calibrationData];
    
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

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
