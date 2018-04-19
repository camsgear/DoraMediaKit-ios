//
//  LayerPixer.h
//  DORADemo
//
//  Created by wuping on 2017/11/14.
//  Copyright © 2017年 DORAPlayer. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <VideoToolbox/VideoToolbox.h>
#import "VideoFileParser.h"
typedef enum _FRAMETYPE {
    FRAMETYPE_I    =      0,//sps+pps+I
    FRAMETYPE_P    =      1,
    FRAMETYPE_SPS  =      2,
    FRAMETYPE_PPS  =      3,
    FRAMETYPE_SEI  =      4
}FRAMETYPE;
@protocol PackSortDelegate <NSObject>

-(void)sortPackData:(VideoPacket *)pack frameType:(FRAMETYPE)type;

@end

@interface LayerPixer : NSObject
{
//    NSData *sps;
//    NSData *pps;
}
typedef void(^DecodePiexBufResult)(CVPixelBufferRef ref);           //解码结果回调
@property(nonatomic,weak)id<PackSortDelegate>delegate;
@property(nonatomic,assign)BOOL isKey;
@property(nonatomic,strong)NSString *videoRecordPath;
@property(nonatomic,strong)DecodePiexBufResult pixerResults;

@property (nonatomic, assign) BOOL closeFileParser;

+ (LayerPixer *)defaultPixer;
/**
 *  对文件的Decode
 *  @param fileName
 *  @param fileExt
 */

-(void)decodeFile:(NSString*)fileName fileExt:(NSString*)fileExt;

@end
