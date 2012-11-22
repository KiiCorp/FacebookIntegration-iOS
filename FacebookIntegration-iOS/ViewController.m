//
//  ViewController.m
//  FacebookIntegration-iOS
//
//  Created by Chris Beauchamp on 11/21/12.
//  Copyright (c) 2012 Kii. All rights reserved.
//

#import "ViewController.h"

#import <KiiSDK/Kii.h>

@implementation ViewController

- (void) userLoggedIn:(KiiUser*)user
            toNetwork:(KiiSocialNetworkName)network
            withError:(KiiError*)error {
    
    NSLog(@"Logged in user: %@ toNetwork: %d withError: %@", user, network, error);
    
    [user describe];
    
}


- (IBAction)logIn:(id)sender {
    
    [KiiSocialConnect setupNetwork:kiiSCNFacebook
                           withKey:@"262612763838475"
                         andSecret:@"8beb4a3bf93138965ecab3f818333a9a"
                        andOptions:nil];
    
    [KiiSocialConnect logIn:kiiSCNFacebook
               usingOptions:nil
               withDelegate:self
                andCallback:@selector(userLoggedIn:toNetwork:withError:)];
    

    
}

@end
