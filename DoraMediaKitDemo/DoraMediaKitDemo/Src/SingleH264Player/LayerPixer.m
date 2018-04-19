//
//  LayerPixer.m
//  DORADemo
//
//  Created by wuping on 2017/11/14.
//  Copyright © 2017年 DORAPlayer. All rights reserved.
//


#import "LayerPixer.h"
#import "VideoFileParser.h"

static uint8_t KStartCode[5] = {0, 0, 0, 1};

typedef uint32_t uint32, uint32_be, uint32_le;

@interface LayerPixer()
{
    uint8_t *_sps;
    NSInteger _spsSize;
    uint8_t *_pps;
    NSInteger _ppsSize;
    uint8_t *_sei;
    NSInteger _seiSize;
    int counts;
    
    VTDecompressionSessionRef _deocderSession;
    CMVideoFormatDescriptionRef _decoderFormatDescription;
}

@end



@implementation LayerPixer

+ (LayerPixer *)defaultPixer
{
    static LayerPixer *defaults = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{
        defaults = [[self alloc] init];
    });
    return defaults;
}



-(void)decodeFile:(NSString*)fileName fileExt:(NSString*)fileExt
{
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        while (true) {
            if (_closeFileParser) {
                break;
            }
            
            NSString *path = [[NSBundle mainBundle] pathForResource:fileName ofType:fileExt];
            NSMutableData *da = [NSMutableData dataWithContentsOfFile:path options:NSDataReadingMappedIfSafe error:nil];
            NSMutableData *data = [NSMutableData dataWithBytes:KStartCode length:4];
            [da appendData:data];
            [self distributepackOf:da];
        }
    });
}

-(void)distributepackOf:(NSData *)inputData
{
    VideoFileParser *parser = [VideoFileParser alloc];
    [parser open:inputData];
    VideoPacket *vp = nil;
    while(true)
    {
        if (_closeFileParser) {
            break;
        }
        
        vp = [parser nextPacket];
        if(vp == nil)
        {
            break;
        }
        [self anlyseFrameVideoPack:vp];
        [NSThread sleepForTimeInterval:0.015];
    }
//    free(vp.buffer);
    [parser close];
    return;
}

-(void)anlyseFrameVideoPack:(VideoPacket *)vp
{
    if (vp.size < 5) {
        return;
    }
    FRAMETYPE type;
    int nalType = vp.buffer[4] & 0x1F;
    VideoPacket *videoPack = vp;
    BOOL isCallBack =false;
    switch (nalType)
    {
        case 0x05:
            if (!_spsSize || !_ppsSize ) {
                return;
            }
            if (_spsSize && _ppsSize) {
                VideoPacket *vp_t = [[VideoPacket alloc] initWithSize:_spsSize+_ppsSize+_seiSize+vp.size];
                memcpy(vp_t.buffer, _sps, _spsSize);
                memcpy(vp_t.buffer+_spsSize, _pps, _ppsSize);
                memcpy(vp_t.buffer+_spsSize+_ppsSize, _sei, _seiSize);
                memcpy(vp_t.buffer+_spsSize+_ppsSize+_seiSize, vp.buffer, vp.size);
                videoPack = vp_t;
            }
            type = FRAMETYPE_I;
            isCallBack = true;
//            NSLog(@"🍑🍑->I size = %ld",vp.size);
            break;
        case 0x07:
            type = FRAMETYPE_SPS;
            if (!_spsSize) {
                _sps = (uint8_t *)malloc(vp.size);
                memset(_sps, 0, vp.size);
                memcpy(_sps, vp.buffer, vp.size);
                _spsSize = vp.size;
            }
//            NSLog(@"🍑🍑->SPS = %ld",vp.size);
            break;
        case 0x08:
            type = FRAMETYPE_PPS;
            if (!_ppsSize) {
                _pps = (uint8_t *)malloc(vp.size);
                memset(_pps,0 , vp.size);
                memcpy(_pps, vp.buffer, vp.size);
                _ppsSize = vp.size;
            }
//            NSLog(@"🍑🍑->PPS = %ld",vp.size);
            break;
        case 0x06: //SEI
            type = FRAMETYPE_SEI;
            if (!_seiSize) {
                _sei = (UInt8 *)malloc(vp.size);
                memset(_sei, 0, vp.size);
                memcpy(_sei, vp.buffer, vp.size);
                _seiSize = vp.size;
            }
//            NSLog(@"🍑🍑->SEI = %ld",vp.size);
            break;
        default:
            //            NSLog(@"苹果TypePB = %d",nalType);
            type = FRAMETYPE_P;
            isCallBack = true;
//            NSLog(@"🍑🍑->P = %ld",vp.size);
            break;
    }
    
    if ([_delegate respondsToSelector:@selector(sortPackData:frameType:)]&& isCallBack) {
        [_delegate sortPackData:videoPack frameType:type];
    }
}

@end

