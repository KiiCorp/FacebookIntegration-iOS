//
//  Kii.h
//  SampleApp
//
//  Created by Chris Beauchamp on 12/11/11.
//  Copyright (c) 2011 Chris Beauchamp. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "KiiBucket.h"
#import "KiiError.h"
#import "KiiObject.h"
#import "KiiUser.h"
#import "KiiGroup.h"
#import "KiiFile.h"
#import "KiiFileBucket.h"
#import "KiiUtilities.h"
#import "KiiRequest.h"
#import "KiiClause.h"
#import "KiiQuery.h"
#import "KiiAnyAuthenticatedUser.h"
#import "KiiAnonymousUser.h"
#import "KiiACL.h"
#import "KiiACLEntry.h"
#import "KiiSocialConnect.h"

@class KiiFile, KiiUser, KiiBucket, KiiGroup;

enum {
    kiiSiteUS,
    kiiSiteJP
};
typedef NSUInteger KiiSite;


/** The main SDK class
 
 This class must be initialized on application launch using beginWithID:andKey:. This class also allows the application to make some high-level user calls and access some application-wide data at any time using static methods.
 */
@interface Kii : NSObject


/** Initialize the Kii SDK
 
 Defaults to the US deployment. Should reside in applicationDidFinishLaunching:withResult:
 @param appId The application ID found in your Kii developer console
 @param appKey The application key found in your Kii developer console
 */
+ (void) beginWithID:(NSString*)appId andKey:(NSString*)appKey;

/** Initialize the Kii SDK
 
 Should reside in applicationDidFinishLaunching:withResult:
 If Kii has provided a custom URL, use this initializer to set it
 @param appId The application ID found in your Kii developer console
 @param appKey The application key found in your Kii developer console
 @param kiiSite One of the enumerator constants kiiSiteUS (United States) or kiiSiteJP (Japan), based on your desired location
 */
+ (void) beginWithID:(NSString*)appId andKey:(NSString*)appKey andSite:(KiiSite)kiiSite;
+ (void) beginWithID:(NSString*)appId andKey:(NSString*)appKey andCustomURL:(NSString*)customURL;


/** Get or create a bucket at the application level
 
 @param bucketName The name of the bucket you'd like to use
 @return An instance of a working KiiBucket
 */
+ (KiiBucket*) bucketWithName:(NSString*)bucketName;


/** Kii SDK Build Number
 @return An NSString object representing the current build number of the SDK
 */
+ (NSString*) getBuildNumber;

/** Kii SDK Version Number
 @return An NSString object representing the current version number of the SDK
 */
+ (NSString*) getSDKVersion;


/** Creates a reference to a group with the given name
 
 If the group already exists, it should be be 'refreshed' to fill the data from the server
 @param groupName An application-specific group name
 @return a working KiiGroup
 */
+ (KiiGroup*) groupWithName:(NSString*)groupName;


/** Creates a reference to a group with the given name with default members
 
 If the group already exists, it should be be 'refreshed' to fill the data from the server
 @param groupName An application-specific group name
 @param members An array of members to automatically add to the group upon creation
 @return a working KiiGroup
 */
+ (KiiGroup*) groupWithName:(NSString*)groupName andMembers:(NSArray*)members;


@end
