//
//  DORAPlayer.h
//  DORAMediaFramework
//
//  Created by wuping on 18/11/2017.
//  Copyright © 2017 camdora. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DORAFFOptions;

/**
 全景视频视图模式类型
 */
typedef enum DORAPanoPerspectiveMode {
    DORAPanoPerspectiveModeFisheye = 0,   // 鱼眼
    DORAPanoPerspectiveModeLittlePlanet,  // 小行星
    DORAPanoPerspectiveModeNormal,        // 普通
} DORAPanoPerspectiveMode;

/**
 全景视频Mount模式类型
 */
typedef enum DORAPanoMountMode {
    DORAPanoMountModeFloor         = 0,
    DORAPanoMountModeWall,
    DORAPanoMountModeCeiling,
} DORAPanoMountMode;

/**
 显示时间模式
 */
typedef enum DORAMeidaTimeMode {
    DORAMeidaTimeModeNone         = 0,  // 不显示
    DORAMeidaTimeModeLeftBottom,
    DORAMeidaTimeModeRightBottom,
    DORAMeidaTimeModeRightTop,
    DORAMeidaTimeModeLeftTop
} DORAMeidaTimeMode;




@interface DORAPlayer : NSObject

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

@end


