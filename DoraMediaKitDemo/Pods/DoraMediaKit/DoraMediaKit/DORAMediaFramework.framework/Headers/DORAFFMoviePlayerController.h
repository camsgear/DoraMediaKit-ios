/*
 * DORAFFMoviePlayerController.h
 *
 * Created by Edwin Cen on 6/30/16.
 * Copyright © 2016 camdora. All rights reserved.
 *
 * This file is part of doraPlayer.
 *

 */

#import "DORAMediaPlayback.h"
#import "DORAFFMonitor.h"
#import "DORAFFOptions.h"

// media meta
#define k_DORAM_KEY_FORMAT         @"format"
#define k_DORAM_KEY_DURATION_US    @"duration_us"
#define k_DORAM_KEY_START_US       @"start_us"
#define k_DORAM_KEY_BITRATE        @"bitrate"

// stream meta
#define k_DORAM_KEY_TYPE           @"type"
#define k_DORAM_VAL_TYPE__VIDEO    @"video"
#define k_DORAM_VAL_TYPE__AUDIO    @"audio"
#define k_DORAM_VAL_TYPE__UNKNOWN  @"unknown"

#define k_DORAM_KEY_CODEC_NAME      @"codec_name"
#define k_DORAM_KEY_CODEC_PROFILE   @"codec_profile"
#define k_DORAM_KEY_CODEC_LONG_NAME @"codec_long_name"

// stream: video
#define k_DORAM_KEY_WIDTH          @"width"
#define k_DORAM_KEY_HEIGHT         @"height"
#define k_DORAM_KEY_FPS_NUM        @"fps_num"
#define k_DORAM_KEY_FPS_DEN        @"fps_den"
#define k_DORAM_KEY_TBR_NUM        @"tbr_num"
#define k_DORAM_KEY_TBR_DEN        @"tbr_den"
#define k_DORAM_KEY_SAR_NUM        @"sar_num"
#define k_DORAM_KEY_SAR_DEN        @"sar_den"
// stream: audio
#define k_DORAM_KEY_SAMPLE_RATE    @"sample_rate"
#define k_DORAM_KEY_CHANNEL_LAYOUT @"channel_layout"

#define kk_DORAM_KEY_STREAMS       @"streams"

// video meta
#define k_DORAM_KEY_VIDEO_TYPE                    @"videoType"
#define k_DORAM_KEY_VIEW_WIDTH                    @"viewWidth"
#define k_DORAM_KEY_VIEW_HEIGHT                   @"viewHeight"
#define k_DORAM_VAL_VIDEO_TYPE_NORMAL             @"Normal"
#define k_DORAM_VAL_VIDEO_TYPE_STEREO_HALF_SPHERE @"StereoHemisphere"
#define k_DORAM_VAL_VIDEO_TYPE_STEREO_FLAT        @"StereoFlat"
#define k_DORAM_VAL_VIDEO_TYPE_STEREO_SPHERE      @"StereoPanorama"
#define k_DORAM_VAL_VIDEO_TYPE_PANORAMA           @"Panorama"

typedef enum DORALogLevel {
    k_DORA_LOG_UNKNOWN = 0,
    k_DORA_LOG_DEFAULT = 1,

    k_DORA_LOG_VERBOSE = 2,
    k_DORA_LOG_DEBUG   = 3,
    k_DORA_LOG_INFO    = 4,
    k_DORA_LOG_WARN    = 5,
    k_DORA_LOG_ERROR   = 6,
    k_DORA_LOG_FATAL   = 7,
    k_DORA_LOG_SILENT  = 8,
} DORALogLevel;

typedef enum DORAPerspectiveMode {
    DORAPerspectiveModeFisheye = 0,
    DORAPerspectiveModeLittlePlanet,
    DORAPerspectiveModeNormal,
} DORAPerspectiveMode;

typedef enum DORA3DViewMode {
    LEFT_EYE = 0,
    FULL_SCREEN,
    BARE_EYE,
} DORA3DViewMode;

typedef enum DORASplitViewMode {
    DORASplitViewModeNormal         = 0,
    DORASplitViewModeSplitFour      = 1,
} DORASplitViewMode;

typedef enum DORAMountMode {
    DORAMountModeFloor         = 0,
    DORAMountModeWall,
    DORAMountModeCeiling,
} DORAMountMode;

typedef enum DORAMeidaTimestampMode {
    DORAMeidaTimestampModeNone         = 0,
    DORAMeidaTimestampModeLeftBottom,
    DORAMeidaTimestampModeRightBottom,
    DORAMeidaTimestampModeRightTop,
    DORAMeidaTimestampModeLeftTop
} DORAMeidaTimestampMode;


@interface DORAFFMoviePlayerController : NSObject <DORAMediaPlayback, UIGestureRecognizerDelegate>

- (id)initWithContentURL:(NSURL *)aUrl
             withOptions:(DORAFFOptions *)options withOtherOptions:(NSDictionary *)otherOptions;

- (id)initWithContentURLString:(NSString *)aUrlString
                   withOptions:(DORAFFOptions *)options withOtherOptions:(NSDictionary *)otherOptions;

- (id)initWithContentURLString: (NSString *)aUrlString
                   withOptions:(DORAFFOptions *)options
                withPlayerSize:(CGSize)size
                 withMediaInfo:(NSDictionary *)mediaInfo;

- (id)initWithContentURLString: (NSString *)aUrlString
                   withOptions:(DORAFFOptions *)options
                withPlayerSize:(CGSize)size
                 withMediaInfo:(NSDictionary *)mediaInfo
           withCalibrationData:(NSString *)calibrationData;

- (void)prepareToPlay;
- (void)play;
- (void)pause;
- (void)stop;
- (BOOL)isPlaying;

- (void)setPauseInBackground:(BOOL)pause;
- (BOOL)isVideoToolboxOpen;

+ (void)setLogReport:(BOOL)preferLogReport;
+ (void)setLogLevel:(DORALogLevel)logLevel;
+ (BOOL)checkIfFFmpegVersionMatch:(BOOL)showAlert;
+ (BOOL)checkIfPlayerVersionMatch:(BOOL)showAlert
                            major:(unsigned int)major
                            minor:(unsigned int)minor
                            micro:(unsigned int)micro;

@property(nonatomic, readonly) CGFloat fpsInMeta;
@property(nonatomic, readonly) CGFloat fpsAtOutput;

- (void)setOptionValue:(NSString *)value
                forKey:(NSString *)key
            ofCategory:(DORAFFOptionCategory)category;

- (void)setOptionIntValue:(int64_t)value
                   forKey:(NSString *)key
               ofCategory:(DORAFFOptionCategory)category;



- (void)setFormatOptionValue:       (NSString *)value forKey:(NSString *)key;
- (void)setCodecOptionValue:        (NSString *)value forKey:(NSString *)key;
- (void)setSwsOptionValue:          (NSString *)value forKey:(NSString *)key;
- (void)setPlayerOptionValue:       (NSString *)value forKey:(NSString *)key;

- (void)setFormatOptionIntValue:    (int64_t)value forKey:(NSString *)key;
- (void)setCodecOptionIntValue:     (int64_t)value forKey:(NSString *)key;
- (void)setSwsOptionIntValue:       (int64_t)value forKey:(NSString *)key;
- (void)setPlayerOptionIntValue:    (int64_t)value forKey:(NSString *)key;

- (void)setViewportRotation: (float)x y:(float)y z:(float)z;
- (void)enterVRMode;
- (void)exitVRMode;
- (void)setVideoUrl: (NSString *)urlString;
- (void)addGestureTo: (UIView *)view;
- (void)removeGestures;
- (void)applyFilter: (int)filterID withFilterResource:(NSArray *)filterResource;
- (void) rotateTo: (UIInterfaceOrientation)orientation;
- (void) setAutoRotate:(BOOL)isOpen;
- (void) setGyroActive:(BOOL)isActive;
- (void) changePerspectiveMode:(DORAPerspectiveMode)mode;
- (void) resetAngle;
- (void) switch3DMode:(DORA3DViewMode)mode;

- (void)setSplitScreenMode:(DORASplitViewMode)mode;
- (void)selectSplitViewAtIndex:(int)index;
- (void)setMountMode:(DORAMountMode)mode;

- (void)setMeidaTimestampMode:(DORAMeidaTimestampMode)mode;

- (void)setMute:(BOOL)isMute;
- (BOOL)checkVideoDataIsEmpty;

- (id)initSingleH264FrameWithOptions:(DORAFFOptions *)options
                      withPlayerSize:(CGSize)size
                       withMediaInfo:(NSDictionary *)mediaInfo
                 withCalibrationData:(NSString *)calibrationData;
- (void)inputSingleH264Data:(uint8_t *)bytes length:(long)length;
- (void)singleH264Shutdown;

- (void)playLastFrame;

@property (nonatomic, retain) id<DORAMediaUrlOpenDelegate> segmentOpenDelegate;
@property (nonatomic, retain) id<DORAMediaUrlOpenDelegate> tcpOpenDelegate;
@property (nonatomic, retain) id<DORAMediaUrlOpenDelegate> httpOpenDelegate;
@property (nonatomic, retain) id<DORAMediaUrlOpenDelegate> liveOpenDelegate;

@property (nonatomic, retain) id<DORAMediaNativeInvokeDelegate> nativeInvokeDelegate;

- (void)didShutdown;

#pragma mark KVO properties
@property (nonatomic, readonly) DORAFFMonitor *monitor;

@end

#define DORA_FF_IO_TYPE_READ (1)
void DORAFFIOStatDebugCallback(const char *url, int type, int bytes);
void DORAFFIOStatRegister(void (*cb)(const char *url, int type, int bytes));

void DORAFFIOStatCompleteDebugCallback(const char *url,
                                      int64_t read_bytes, int64_t total_size,
                                      int64_t elpased_time, int64_t total_duration);
void DORAFFIOStatCompleteRegister(void (*cb)(const char *url,
                                            int64_t read_bytes, int64_t total_size,
                                            int64_t elpased_time, int64_t total_duration));
