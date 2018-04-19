# DoraMediaKit-ios

## 集成SDK
通过cocoapods集成方式
```pod 'DoraMediaKit'```
添加之后执行 pod install / pod update 命令即可。

## DORAMediaFramework使用
导入头文件
```#import <DORAMediaFramework/DORAMediaFramework.h>```

## 播放器使用
```Object-C
	DORAPlayer *player = [DORAPlayer sharedPlayer];
	DORAFFOptions *options = [DORAFFOptions optionsByDefault];
	NSString *mediaStr = @"xxxxxxx";
	NSString *calibration = @"version=v1&type=1&data=0.495870,0.494145,0.505515,1.753980,3.000000,-0.002005,-0.002005,0.999998,2.000000,-0.045891,-0.045875,0.998947,1.000000,-0.005371,-0.005370,0.999986;0.495394,1.511058,0.502757,1.753863,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000;0.602270,0.874488,0.940670,0.969515,0.526458,0.627032,0.961586,0.904201,0.206726,0.508845,0.352884,0.560779,0.411990,0.498598,0.070204,0.821680;0.733293,0.050407,0.425355,0.921722,0.777676,0.640256,0.133516,0.093034,0.530997,0.503261,0.269104,0.748532,0.495609,0.128849,0.832392,0.516214";
    
    NSDictionary *mediaInfo = @{
//                                                                @"count" : @"2",
                                //                                @"fov" : @"210",
                                //                                @"fps" : @"30",
                                //                                @"height" : @"1080",
                                //                                @"mount" : @"0",
//                                                                @"needStitch" : @"1",
                                //                                @"order" : @"2",
                                //                                @"orientation" : @"0",
                                                                @"projection" : @"0",
                                //                                @"width" : @"1080"
                                };
    
    [player setContentURLString:mediaStr withOptions:options withPlayerSize:CGSizeMake(kScreenWidth, kScreenWidth) withMediaInfo:mediaInfo withCalibrationData:calibration];
    //添加全景播放的手势
    [player addGestureTo:self.displayView];
    //添加到视图中
    [self.displayView addSubview:player.displayView];
    [player prepareToPlay];
```

## 接口详细说明
```Object-C
/**
 视频输出的视图
 */
@property (nonatomic, weak) UIView *displayView;

/**
 创建播放器单例
 
 @return 播放器单例
 */
+ (DORAPlayer *)sharedPlayer;


/**
 初始化播放器传入相关参数
 
 @param aUrlString 播放器播放地址
 eg: rtsp://192.168.0.1/8
 
 @param options 设置播放器参数
 eg: DORAFFOptions *options = [DORAFFOptions optionsByDefault];
 [options setFormatOptionValue:@"tcp" forKey:@"rtsp_transport"];
 ...
 
 @param size 播放器视图大小
 eg:(375, 375)
 
 @param mediaInfo 视频相关参数
 count 一帧中单幅画面的数量             eg: 1/2
 needStitch 是否需要拼接              eg: true/false
 projection 一帧中单幅画面的投影类型    eg: 0:全景鱼眼图; 1:全景展开图 2:普通2D图
 width 一帧中单幅画面的宽              eg: 1080
 height 一帧中单幅画面的高             eg: 1080/1920
 fov    一帧中单幅画面的FOV(Degree)   eg: 185/190/210/220
 fps    视频一秒帧数                  eg: 30/60
 mount  一帧中单幅画面的挂载方式        eg: 0:水平放置; 1:倒立挂置
 order  一帧中画面的排列顺序           eg: 0:左->右; 1:右->左; 2:上->下; 3:下->上
 rientation 一帧中单幅画面的旋转角度    eg: 90/180/270
 
 @param calibrationData 拼接参数
 eg: @"version=v1&type=1&data=***"
 */
- (void)setContentURLString: (NSString *)aUrlString
                withOptions:(DORAFFOptions *)options
             withPlayerSize:(CGSize)size
              withMediaInfo:(NSDictionary *)mediaInfo
        withCalibrationData:(NSString *)calibrationData;


/**
 全景视频播放时，需要传入手势滑动的视图层
 
 @param view 滑动手势视图
 */
- (void)addGestureTo: (UIView *)view;

/**
 全景视频播放时，设置陀螺仪状态
 @param isActive 陀螺仪是否开启
 */
- (void)setGyroActive: (BOOL) isActive;


/**
 初始化播放器后，调用此接口开始播放视频
 */
- (void)prepareToPlay;

/**
 视频继续播放
 */
- (void)play;

/**
 视频暂停播放
 */
- (void)pause;

/**
 视频停止播放
 */
- (void)stop;

/**
 播放器停止播放，且释放播放器
 */
- (void)shutdown;

/**
 修改全景视频视图观看模式
 
 @param mode 视图观看模式
 */
- (void)changePerspectiveMode:(DORAPanoPerspectiveMode)mode;

/**
 根据当前模式重置视角为初始状态
 */
- (void)resetAngle;

/**
 修改全景视频或鱼眼视频的Mount模式
 
 @param mode mount模式
 */
- (void)changeMountMode:(DORAPanoMountMode)mode;


/**
 显示当前播放时间模式 默认（不显示）

 @param mode 显示模式
 */
- (void)setMeidaTimeMode:(DORAMeidaTimeMode)mode;


#pragma mark - 单帧H264播放器
/**
 初始化单帧H264播放器传入相关参数
 
 @param size 播放器视图大小
 eg:(375, 375)
 
 @param mediaInfo 视频相关参数
 count 一帧中单幅画面的数量             eg: 1/2
 needStitch 是否需要拼接              eg: true/false
 projection 一帧中单幅画面的投影类型    eg: 0:全景鱼眼图; 1:全景展开图 2:普通2D图
 width 一帧中单幅画面的宽              eg: 1080
 height 一帧中单幅画面的高             eg: 1080/1920
 fov    一帧中单幅画面的FOV(Degree)   eg: 185/190/210/220
 fps    视频一秒帧数                  eg: 30/60
 mount  一帧中单幅画面的挂载方式        eg: 0:水平放置; 1:倒立挂置
 order  一帧中画面的排列顺序           eg: 0:左->右; 1:右->左; 2:上->下; 3:下->上
 rientation 一帧中单幅画面的旋转角度    eg: 90/180/270
 
 @param calibrationData 拼接参数
 eg: @"version=v1&type=1&data=***"
 */
- (void)setSingleH264WithPlayerSize:(CGSize)size
                      withMediaInfo:(NSDictionary *)mediaInfo
                withCalibrationData:(NSString *)calibrationData;


/**
 输入单帧H264数据和数据长度
 
 @param bytes 单帧H264数据
 @param length 单帧H264数据长度
 */
- (void)inputSingleH264Data:(uint8_t *)bytes length:(long)length;

/**
 播放器停止单帧播放，且释放播放器
 */
- (void)singleH264PlayerShutdown;

/**
 播放当前最后一帧
 */
- (void)playLastFrame;
```



