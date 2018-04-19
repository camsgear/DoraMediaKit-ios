/*
 * DORAMediaFramework.h
 *
 * Created by Edwin Cen on 6/30/16.
 * Copyright © 2016 camdora. All rights reserved.
 *
 * This file is part of doraPlayer.
 *
 */

#import <UIKit/UIKit.h>

//! Project version number for DORAMediaFramework.
FOUNDATION_EXPORT double DORAMediaFrameworkVersionNumber;

//! Project version string for DORAMediaFramework.
FOUNDATION_EXPORT const unsigned char DORAMediaFrameworkVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <DORAMediaFramework/PublicHeader.h>

#import <DORAMediaFramework/DORAPlayer.h>
#import <DORAMediaFramework/DORAFFOptions.h>
#import <DORAMediaFramework/DORAMediaPlayback.h>
#import <DORAMediaFramework/DORAFFMoviePlayerController.h>
#import <DORAMediaFramework/DORAMediaModule.h>
#import <DORAMediaFramework/DORAMediaPlayer.h>
#import <DORAMediaFramework/DORANotificationManager.h>
#import <DORAMediaFramework/DORAKVOController.h>

// backward compatible for old names
#define DORAMediaPlaybackIsPreparedToPlayDidChangeNotification DORAMPMediaPlaybackIsPreparedToPlayDidChangeNotification
#define DORAMoviePlayerLoadStateDidChangeNotification DORAMPMoviePlayerLoadStateDidChangeNotification
#define DORAMoviePlayerPlaybackDidFinishNotification DORAMPMoviePlayerPlaybackDidFinishNotification
#define DORAMoviePlayerPlaybackDidFinishReasonUserInfoKey DORAMPMoviePlayerPlaybackDidFinishReasonUserInfoKey
#define DORAMoviePlayerPlaybackStateDidChangeNotification DORAMPMoviePlayerPlaybackStateDidChangeNotification
#define DORAMoviePlayerIsAirPlayVideoActiveDidChangeNotification DORAMPMoviePlayerIsAirPlayVideoActiveDidChangeNotification
#define DORAMoviePlayerVideoDecoderOpenNotification DORAMPMoviePlayerVideoDecoderOpenNotification
#define DORAMoviePlayerFirstVideoFrameRenderedNotification DORAMPMoviePlayerFirstVideoFrameRenderedNotification
#define DORAMoviePlayerFirstAudioFrameRenderedNotification DORAMPMoviePlayerFirstAudioFrameRenderedNotification

