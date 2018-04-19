/*
 * DORAFFOptions.h
 *
 * Created by Edwin Cen on 6/30/16.
 * Copyright © 2016 camdora. All rights reserved.
 *
 * This file is part of doraPlayer.
 *

 */

#import <Foundation/Foundation.h>

typedef enum DORAFFOptionCategory {
    kDORAFFOptionCategoryFormat = 1,
    kDORAFFOptionCategoryCodec  = 2,
    kDORAFFOptionCategorySws    = 3,
    kDORAFFOptionCategoryPlayer = 4,
} DORAFFOptionCategory;

// for codec option 'skip_loop_filter' and 'skip_frame'
typedef enum DORAAVDiscard {
    /* We leave some space between them for extensions (drop some
     * keyframes for intra-only or drop just some bidir frames). */
    DORA_AVDISCARD_NONE    =-16, ///< discard nothing
    DORA_AVDISCARD_DEFAULT =  0, ///< discard useless packets like 0 size packets in avi
    DORA_AVDISCARD_NONREF  =  8, ///< discard all non reference
    DORA_AVDISCARD_BIDIR   = 16, ///< discard all bidirectional frames
    DORA_AVDISCARD_NONKEY  = 32, ///< discard all frames except keyframes
    DORA_AVDISCARD_ALL     = 48, ///< discard all
} DORAAVDiscard;

struct DoraMediaPlayer;

@interface DORAFFOptions : NSObject

+(DORAFFOptions *)optionsByDefault;
+(DORAFFOptions *)optionsRTSP;
+ (DORAFFOptions *)optionsRTMP;
+ (DORAFFOptions *)optionsP2P;

-(void)applyTo:(struct DoraMediaPlayer *)mediaPlayer;

- (void)setOptionValue:(NSString *)value
                forKey:(NSString *)key
            ofCategory:(DORAFFOptionCategory)category;

- (void)setOptionIntValue:(int64_t)value
                   forKey:(NSString *)key
               ofCategory:(DORAFFOptionCategory)category;


-(void)setFormatOptionValue:       (NSString *)value forKey:(NSString *)key;
-(void)setCodecOptionValue:        (NSString *)value forKey:(NSString *)key;
-(void)setSwsOptionValue:          (NSString *)value forKey:(NSString *)key;
-(void)setPlayerOptionValue:       (NSString *)value forKey:(NSString *)key;

-(void)setFormatOptionIntValue:    (int64_t)value forKey:(NSString *)key;
-(void)setCodecOptionIntValue:     (int64_t)value forKey:(NSString *)key;
-(void)setSwsOptionIntValue:       (int64_t)value forKey:(NSString *)key;
-(void)setPlayerOptionIntValue:    (int64_t)value forKey:(NSString *)key;

@end
