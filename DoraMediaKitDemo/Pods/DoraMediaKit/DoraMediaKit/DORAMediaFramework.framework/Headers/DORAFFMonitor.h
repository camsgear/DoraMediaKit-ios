/*
 * Created by Edwin Cen on 6/30/16.
 * Copyright © 2016 camdora. All rights reserved.
 *
 * This file is part of doraPlayer.
 *

 */

#import <Foundation/Foundation.h>

@interface DORAFFMonitor : NSObject

- (instancetype)init;

@property(nonatomic) NSDictionary *mediaMeta;
@property(nonatomic) NSDictionary *videoMeta;
@property(nonatomic) NSDictionary *audioMeta;

@property(nonatomic, readonly) int64_t   duration;   // milliseconds
@property(nonatomic, readonly) int64_t   bitrate;    // bit / sec
@property(nonatomic, readonly) float     fps;        // frame / sec
@property(nonatomic, readonly) int       width;      // width
@property(nonatomic, readonly) int       height;     // height
@property(nonatomic, readonly) NSString *vcodec;     // video codec
@property(nonatomic, readonly) NSString *acodec;     // audio codec

@property(nonatomic) int       tcpError;
@property(nonatomic) NSString *remoteIp;

@property(nonatomic) int       httpError;
@property(nonatomic) NSString *httpUrl;
@property(nonatomic) NSString *httpHost;
@property(nonatomic) int       httpCode;
@property(nonatomic) int64_t   httpOpenTick;
@property(nonatomic) int64_t   httpSeekTick;

@end
