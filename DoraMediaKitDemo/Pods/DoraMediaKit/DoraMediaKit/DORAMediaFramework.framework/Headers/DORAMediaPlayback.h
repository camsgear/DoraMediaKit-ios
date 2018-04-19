/*
 * DORAMediaPlayback.h
 *
 * Created by Edwin Cen on 6/30/16.
 * Copyright © 2016 camdora. All rights reserved.
 *
 * This file is part of doraPlayer.
 *

 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, DORAMPMovieType) {
    DORAMPMovieTypeNormal,           // Normal video without 3d or panorama
    DORAMPMovieTypeStereoHalfSphere, // 3d video with 180 degree
    DORAMPMovieTypeStereoSphere,     // 3d video with 360 degree full panorama
    DORAMPMovieTypeStereoFlat,       // 3d video with less then 180 degree flat
    DORAMPMovieTypePanorama          // full panorama without stereo effect
};

typedef NS_ENUM(NSInteger, DORAMPMovieScalingMode) {
    DORAMPMovieScalingModeNone,       // No scaling
    DORAMPMovieScalingModeAspectFit,  // Uniform scale until one dimension fits
    DORAMPMovieScalingModeAspectFill, // Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    DORAMPMovieScalingModeFill        // Non-uniform scale. Both render dimensions will exactly match the visible bounds
};

typedef NS_ENUM(NSInteger, DORAMPMoviePlaybackState) {
    DORAMPMoviePlaybackStateStopped,
    DORAMPMoviePlaybackStatePlaying,
    DORAMPMoviePlaybackStatePaused,
    DORAMPMoviePlaybackStateInterrupted,
    DORAMPMoviePlaybackStateSeekingForward,
    DORAMPMoviePlaybackStateSeekingBackward
};

typedef NS_OPTIONS(NSUInteger, DORAMPMovieLoadState) {
    DORAMPMovieLoadStateUnknown        = 0,
    DORAMPMovieLoadStatePlayable       = 1 << 0,
    DORAMPMovieLoadStatePlaythroughOK  = 1 << 1, // Playback will be automatically started in this state when shouldAutoplay is YES
    DORAMPMovieLoadStateStalled        = 1 << 2, // Playback will be automatically paused in this state, if started
};

typedef NS_ENUM(NSInteger, DORAMPMovieFinishReason) {
    DORAMPMovieFinishReasonPlaybackEnded,
    DORAMPMovieFinishReasonPlaybackError,
    DORAMPMovieFinishReasonUserExited
};

// -----------------------------------------------------------------------------
// Thumbnails

typedef NS_ENUM(NSInteger, DORAMPMovieTimeOption) {
    DORAMPMovieTimeOptionNearestKeyFrame,
    DORAMPMovieTimeOptionExact
};

@protocol DORAMediaPlayback;

#pragma mark DORAMediaPlayback

@protocol DORAMediaPlayback <NSObject>

- (void)prepareToPlay;
- (void)play;
- (void)pause;
- (void)stop;
- (BOOL)isPlaying;
- (void)shutdown;
- (void)setPauseInBackground:(BOOL)pause;

@property(nonatomic, readonly)  UIView *view;
@property(nonatomic)            NSTimeInterval currentPlaybackTime;
@property(nonatomic, readonly)  NSTimeInterval duration;
@property(nonatomic, readonly)  NSTimeInterval playableDuration;
@property(nonatomic, readonly)  NSInteger bufferingProgress;

@property(nonatomic, readonly)  BOOL isPreparedToPlay;
@property(nonatomic, readonly)  DORAMPMoviePlaybackState playbackState;
@property(nonatomic, readonly)  DORAMPMovieLoadState loadState;

@property(nonatomic, readonly) int64_t numberOfBytesTransferred;

@property(nonatomic, readonly) CGSize naturalSize;
@property(nonatomic) DORAMPMovieScalingMode scalingMode;
@property(nonatomic) BOOL shouldAutoplay;

@property (nonatomic) BOOL allowsMediaAirPlay;
@property (nonatomic) BOOL isDanmakuMediaAirPlay;
@property (nonatomic, readonly) BOOL airPlayMediaActive;

@property (nonatomic) float playbackRate;

- (UIImage *)thumbnailImageAtCurrentTime;

#pragma mark Notifications

#ifdef __cplusplus
#define DORA_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define DORA_EXTERN extern __attribute__((visibility ("default")))
#endif

// -----------------------------------------------------------------------------
//  MPMediaPlayback.h

// Posted when the prepared state changes of an object conforming to the MPMediaPlayback protocol changes.
// This supersedes MPMoviePlayerContentPreloadDidFinishNotification.
DORA_EXTERN NSString *const DORAMPMediaPlaybackIsPreparedToPlayDidChangeNotification;

// -----------------------------------------------------------------------------
//  MPMoviePlayerController.h
//  Movie Player Notifications

// Posted when the scaling mode changes.
DORA_EXTERN NSString* const DORAMPMoviePlayerScalingModeDidChangeNotification;

// Posted when movie playback ends or a user exits playback.
DORA_EXTERN NSString* const DORAMPMoviePlayerPlaybackDidFinishNotification;
DORA_EXTERN NSString* const DORAMPMoviePlayerPlaybackDidFinishReasonUserInfoKey; // NSNumber (DORAMPMovieFinishReason)

// Posted when the playback state changes, either programatically or by the user.
DORA_EXTERN NSString* const DORAMPMoviePlayerPlaybackStateDidChangeNotification;

// Posted when the network load state changes.
DORA_EXTERN NSString* const DORAMPMoviePlayerLoadStateDidChangeNotification;

// Posted when the movie player begins or ends playing video via AirPlay.
DORA_EXTERN NSString* const DORAMPMoviePlayerIsAirPlayVideoActiveDidChangeNotification;

// -----------------------------------------------------------------------------
// Movie Property Notifications

// Calling -prepareToPlay on the movie player will begin determining movie properties asynchronously.
// These notifications are posted when the associated movie property becomes available.
DORA_EXTERN NSString* const DORAMPMovieNaturalSizeAvailableNotification;

// -----------------------------------------------------------------------------
//  Extend Notifications

DORA_EXTERN NSString *const DORAMPMoviePlayerVideoDecoderOpenNotification;
DORA_EXTERN NSString *const DORAMPMoviePlayerFirstVideoFrameRenderedNotification;
DORA_EXTERN NSString *const DORAMPMoviePlayerFirstAudioFrameRenderedNotification;

DORA_EXTERN NSString *const DORAMPMoviePlayerDidSeekCompleteNotification;
DORA_EXTERN NSString *const DORAMPMoviePlayerDidSeekCompleteTargetKey;
DORA_EXTERN NSString *const DORAMPMoviePlayerDidSeekCompleteErrorKey;

@end

#pragma mark DORAMediaUrlOpenDelegate

// Must equal to the defination in doraavformat/doraavformat.h
typedef NS_ENUM(NSInteger, DORAMediaEvent) {
    // Control Messages
    DORAMediaUrlOpenEvent_ConcatResolveSegment = 0x10000,
    DORAMediaUrlOpenEvent_TcpOpen = 0x10001,
    DORAMediaUrlOpenEvent_HttpOpen = 0x10002,
    DORAMediaUrlOpenEvent_LiveOpen = 0x10004,

    // Notify Events
    DORAMediaEvent_WillHttpOpen = 0x12100, // attr: url
    DORAMediaEvent_DidHttpOpen = 0x12101,  // attr: url, error, http_code
    DORAMediaEvent_WillHttpSeek = 0x12102, // attr: url, offset
    DORAMediaEvent_DidHttpSeek = 0x12103,  // attr: url, offset, error, http_code
};

#define DORAMediaEventAttrKey_url            @"url"
#define DORAMediaEventAttrKey_host           @"host"
#define DORAMediaEventAttrKey_error          @"error"
#define DORAMediaEventAttrKey_time_of_event  @"time_of_event"
#define DORAMediaEventAttrKey_http_code      @"http_code"
#define DORAMediaEventAttrKey_offset         @"offset"

// event of DORAMediaUrlOpenEvent_xxx
@interface DORAMediaUrlOpenData: NSObject

- (id)initWithUrl:(NSString *)url
            event:(DORAMediaEvent)event
     segmentIndex:(int)segmentIndex
     retryCounter:(int)retryCounter;

@property(nonatomic, readonly) DORAMediaEvent event;
@property(nonatomic, readonly) int segmentIndex;
@property(nonatomic, readonly) int retryCounter;

@property(nonatomic, retain) NSString *url;
@property(nonatomic) int error; // set a negative value to indicate an error has occured.
@property(nonatomic, getter=isHandled)    BOOL handled;     // auto set to YES if url changed
@property(nonatomic, getter=isUrlChanged) BOOL urlChanged;  // auto set to YES by url changed

@end

@protocol DORAMediaUrlOpenDelegate <NSObject>

- (void)willOpenUrl:(DORAMediaUrlOpenData*) urlOpenData;

@end

@protocol DORAMediaNativeInvokeDelegate <NSObject>

- (int)invoke:(DORAMediaEvent)event attributes:(NSDictionary *)attributes;

@end
