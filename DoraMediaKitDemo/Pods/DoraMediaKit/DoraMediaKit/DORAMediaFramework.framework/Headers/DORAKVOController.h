/*
 * DORAKVOController.h
 *
 * Created by Edwin Cen on 6/30/16.
 * Copyright © 2016 camdora. All rights reserved.
 *
 * This file is part of doraPlayer.
 *

 */

#import <Foundation/Foundation.h>

@interface DORAKVOController : NSObject

- (id)initWithTarget:(NSObject *)target;

- (void)safelyAddObserver:(NSObject *)observer
               forKeyPath:(NSString *)keyPath
                  options:(NSKeyValueObservingOptions)options
                  context:(void *)context;
- (void)safelyRemoveObserver:(NSObject *)observer
                  forKeyPath:(NSString *)keyPath;

- (void)safelyRemoveAllObservers;

@end
