
//
//  CDAGlobalDef.h
//  DORAMediaKit-iOSDemo
//
//  Created by wuping on 21/11/2017.
//  Copyright © 2017 DORAPlayer. All rights reserved.
//

#ifndef CDAGlobalDef_h
#define CDAGlobalDef_h


#define kScreenWidth ([[UIScreen mainScreen] respondsToSelector:@selector(nativeBounds)] ? [UIScreen mainScreen].nativeBounds.size.width/[UIScreen mainScreen].nativeScale : [UIScreen mainScreen].bounds.size.width)

#define kScreenHeight ([[UIScreen mainScreen] respondsToSelector:@selector(nativeBounds)] ? [UIScreen mainScreen].nativeBounds.size.height/[UIScreen mainScreen].nativeScale : [UIScreen mainScreen].bounds.size.height)

#define kStringIsEmpty(str) ([str isKindOfClass:[NSNull class]] || str == nil || [str length] < 1 ? YES : NO )

#ifndef __OPTIMIZE__
#define NSLog(msg,...)\
{NSLog(@"< - %@ - > %@",[NSString stringWithUTF8String:__FUNCTION__], [NSString stringWithFormat:(msg), ##__VA_ARGS__]);}
#else
#define NSLog(...) {}
#endif


#define weakSelf() __weak __typeof__(self) weakSelf = self
#define strongSelf() __strong __typeof(self) self = weakSelf

#endif /* CDAGlobalDef_h */
