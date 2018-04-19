/*
 * DORANotificationManager.h
 *
 * Created by Edwin Cen on 6/30/16.
 * Copyright © 2016 camdora. All rights reserved.
 *
 * This file is part of doraPlayer.
 *

 */

#import <Foundation/Foundation.h>

@interface DORANotificationManager : NSObject

- (nullable instancetype)init;

- (void)addObserver:(nonnull id)observer
           selector:(nonnull SEL)aSelector
               name:(nullable NSString *)aName
             object:(nullable id)anObject;

- (void)removeAllObservers:(nonnull id)observer;

@end
