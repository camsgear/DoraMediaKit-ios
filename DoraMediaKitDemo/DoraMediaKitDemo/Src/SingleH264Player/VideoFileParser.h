//
//  VideoFileParser.h
//  DORADemo
//
//  Created by DORAPlayer on 2017/11/14.
//  Copyright © 2017年 DORAPlayer. All rights reserved.
//

#include <objc/NSObject.h>

@interface VideoPacket : NSObject

@property(nonatomic,assign)uint8_t *buffer;
@property(nonatomic,assign)NSInteger size;

//Options
@property(nonatomic,assign)uint8_t *frmBuffer;
@property(nonatomic,assign)NSInteger frmSize;
@property(nonatomic,assign)long long timeStamp;   //时间戳Buffer


@property(nonatomic,assign)NSInteger validSize;           //上一次存储的位置
@property(nonatomic,assign)BOOL isReadyForDecode;         //准备好了开始解码；
@property(nonatomic,strong)NSMutableArray *storedFrames;  //帧数据存储
@property(nonatomic,strong)NSMutableArray *tmpFrames;

- (instancetype)initWithSize:(NSInteger)size;


@end

@interface VideoFileParser : NSObject
@property(nonatomic,assign)uint8_t *paserBuffer;   //原始数据
@property(nonatomic,assign)NSInteger paserSize;    //原始数据长度
-(BOOL)open:(NSData*)inputData;
-(BOOL)openData:(char *)inputs Length:(NSInteger)length;
-(VideoPacket *)nextPacket;
-(VideoPacket *)nextOriginalPaceket;
-(void)close;
-(void)closeDataPaser;

@end
