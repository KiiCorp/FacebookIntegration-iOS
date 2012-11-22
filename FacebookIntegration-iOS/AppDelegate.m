//
//  AppDelegate.m
//  FacebookIntegration-iOS
//
//  Created by Chris Beauchamp on 11/21/12.
//  Copyright (c) 2012 Kii. All rights reserved.
//

#import "AppDelegate.h"

#import <KiiSDK/Kii.h>

#import "ViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{

    [Kii beginWithID:@"28cdf645" andKey:@"165c5ef22896b3f4bde346124e0548ec"];

    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    self.viewController = [[ViewController alloc] initWithNibName:@"ViewController" bundle:nil];
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    return YES;
}

#pragma mark Social Req's
// Pre iOS 4.2 support
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url {
    return [KiiSocialConnect handleOpenURL:url];
}

// For iOS 4.2+ support
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    return [KiiSocialConnect handleOpenURL:url];
}

@end
