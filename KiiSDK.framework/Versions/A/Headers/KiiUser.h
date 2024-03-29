//
//  KiiUser.h
//  SampleApp
//
//  Created by Chris Beauchamp on 12/14/11.
//  Copyright (c) 2011 Chris Beauchamp. All rights reserved.
//

#import <Foundation/Foundation.h>


/** Contains user profile/account information and methods
 
 The user class allows an application to generate a user, register them with the server and log them in during subsequent sessions. Since KiiUser is similar to KiiObject, the application can also set key/value pairs to this user.
 */

@class KiiBucket, KiiFileBucket;
@interface KiiUser : NSObject

/** The unique id of the KiiUser object, assigned by the server */
@property (readonly) NSString *uuid;

/** Username to use for authentication or for display. Must be between 3 and 64 characters, which can include alphanumeric characters as well as underscores '_' and periods '.' */
@property (readonly) NSString *username;

/** Display name for this user. Cannot be used for logging a user in; is non-unique. */
@property (nonatomic, retain) NSString *displayName;

/** Email address to use for authentication or for display */
@property (readonly) NSString *email;

/** Phone number to use for authentication or for display */
@property (readonly) NSString *phoneNumber;

/** The country code associated with this user */
@property (nonatomic, retain) NSString *country;

/** Whether or not a user has validated their email address. This field is assigned by the server. */
@property (readonly) BOOL emailVerified;

/** Whether or not a user has validated their phone number. This field is assigned by the server. */
@property (readonly) BOOL phoneVerified;

/** The date the user was created on the server */
@property (readonly) NSDate *created;

/** The date the user was last modified on the server */
@property (readonly) NSDate *modified;

/** Get a specifically formatted string referencing the user. The user must exist in the cloud (have a valid UUID). */
@property (readonly) NSString *objectURI;

/** The access token for the user - only available if the user is currently logged in. */
@property (readonly) NSString *accessToken;


/** Create a user object to prepare for registration with credentials pre-filled
 Creates an pre-filled user object for manipulation. This user will not be authenticated until one of the authentication methods are called on it. Custom fields can be added to it before it is registered or authenticated.
 @param userUsername The user's desired username. Must be between 3 and 64 characters, which can include alphanumeric characters as well as underscores '_' and periods '.'
 @param userPassword The user's password. Must be at least 4 characters, made up of alphanumeric and/or: @,#,$,%,^,&
 @return a working KiiUser object
 */
+ (KiiUser*) userWithUsername:(NSString*)userUsername
                  andPassword:(NSString*)userPassword;


/** Create a user object to prepare for registration with credentials pre-filled
 
 Creates an pre-filled user object for registration. This user will not be authenticated until the registration method is called on it. It can be treated as any other KiiUser before it is registered.
 @param phoneNumber The user's phone number
 @param userPassword The user's password. Must be at least 4 characters, made up of alphanumeric and/or: @,#,$,%,^,&
 @return a working KiiUser object
 */
+ (KiiUser*) userWithPhoneNumber:(NSString*)phoneNumber
                     andPassword:(NSString*)userPassword;


/** Create a user object to prepare for registration with credentials pre-filled
 
 Creates an pre-filled user object for registration. This user will not be authenticated until the registration method is called on it. It can be treated as any other KiiUser before it is registered.
 @param emailAddress The user's email address
 @param userPassword The user's password. Must be at least 4 characters, made up of alphanumeric and/or: @,#,$,%,^,&
 @return a working KiiUser object
 */
+ (KiiUser*) userWithEmailAddress:(NSString*)emailAddress
                      andPassword:(NSString*)userPassword;



/** Create a user object to prepare for registration with credentials pre-filled
 
 Creates an pre-filled user object for registration. This user will not be authenticated until the registration method is called on it. It can be treated as any other KiiUser before it is registered.
 @param username The user's desired username. Must be between 3 and 64 characters, which can include alphanumeric characters as well as underscores '_' and periods '.'
 @param phoneNumber The user's phone number
 @param userPassword The user's password. Must be at least 4 characters, made up of alphanumeric and/or: @,#,$,%,^,&
 @return a working KiiUser object
 */
+ (KiiUser*) userWithUsername:(NSString*)username
               andPhoneNumber:(NSString*)phoneNumber
                  andPassword:(NSString*)userPassword;


/** Create a user object to prepare for registration with credentials pre-filled
 
 Creates an pre-filled user object for registration. This user will not be authenticated until the registration method is called on it. It can be treated as any other KiiUser before it is registered.
 @param username The user's desired username. Must be between 3 and 64 characters, which can include alphanumeric characters as well as underscores '_' and periods '.'
 @param emailAddress The user's email address
 @param userPassword The user's password. Must be at least 4 characters, made up of alphanumeric and/or: @,#,$,%,^,&
 @return a working KiiUser object
 */
+ (KiiUser*) userWithUsername:(NSString*)username
              andEmailAddress:(NSString*)emailAddress
                  andPassword:(NSString*)userPassword;


/** Create a KiiUser that references an existing user

 @param uri A user-specific URI
 @return a working KiiUser
 */
+ (KiiUser*) userWithURI:(NSString*)uri;


/** Asynchronously authenticates a user with the server
 
 Authenticates a user with the server. This method is non-blocking.
 @param userIdentifier Can be a username or a verified phone number or a verified email address
 @param password The user's password. Must be at least 4 characters, made up of alphanumeric and/or: @,#,$,%,^,&
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) authenticationComplete:(KiiUser*)user withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // do something with the user
        }
 
        else {
            // there was a problem
        }
    }
 
 */
+ (void) authenticate:(NSString*)userIdentifier
         withPassword:(NSString*)password
          andDelegate:(id)delegate
          andCallback:(SEL)callback;


/** Synchronously authenticates a user with the server
 
 Authenticates a user with the server. This method is blocking.
 @param userIdentifier Can be a username or a verified phone number or a verified email address
 @param password The user's password
 @param error An NSError object, set to nil, to test for errors
 @return The KiiUser object that was authenticated. NULL if failed to authenticate
 */
+ (KiiUser*) authenticateSynchronous:(NSString*)userIdentifier
                        withPassword:(NSString*)password
                            andError:(NSError**)error;


/** Asynchronously authenticates a user with the server using a valid access token
 
 Authenticates a user with the server. This method is non-blocking.
 @param accessToken A valid access token associated with the desired user
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) authenticationComplete:(KiiUser*)user withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
 
 */
+ (void) authenticateWithToken:(NSString*)accessToken
                   andDelegate:(id)delegate
                   andCallback:(SEL)callback;


/** Synchronously authenticates a user with the server using a valid access token
 
 Authenticates a user with the server. This method is blocking.
 @param accessToken A valid access token associated with the desired user
 @param error An NSError object, set to nil, to test for errors
 @return The KiiUser object that was authenticated. NULL if failed to authenticate
 */
+ (KiiUser*) authenticateWithTokenSynchronous:(NSString*)accessToken
                                     andError:(NSError**)error;



/** Asynchronously authenticates a user object with the server
 
 Authenticates a user with the server. The user object must have an associated email/password combination. This method is non-blocking.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) registrationComplete:(KiiUser*)user withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // do something with the user
        }
 
        else {
            // there was a problem
        }
    }
 
 */
- (void) performRegistration:(id)delegate withCallback:(SEL)callback;


/** Synchronously registers a user object with the server
 
 Registers a user with the server. The user object must have an associated email/password combination. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) performRegistrationSynchronous:(NSError**)error;


/** Asynchronously update a user's password on the server
 
 Update a user's password with the server. The fromPassword must be equal to the current password associated with the account in order to succeed. This method is non-blocking.
 @param fromPassword The user's current password
 @param toPassword The user's desired password. Must be at least 4 characters, made up of alphanumeric and/or: @,#,$,%,^,&
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) passwordUpdateComplete:(KiiUser*)user withError:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // do something with the user
        }
 
        else {
            // there was a problem
        }
    }
 
 */
- (void) updatePassword:(NSString*)fromPassword to:(NSString*)toPassword withDelegate:(id)delegate andCallback:(SEL)callback;


/** Synchronously update a user's password on the server
 
 Update a user's password with the server. The fromPassword must be equal to the current password associated with the account in order to succeed. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 @param fromPassword The user's current password
 @param toPassword The user's desired password. Must be at least 4 characters, made up of alphanumeric and/or: @,#,$,%,^,&
 */
- (void) updatePasswordSynchronous:(NSError**)error from:(NSString*)fromPassword to:(NSString*)toPassword;


/** Asynchronously reset a user's password on the server
 
 Reset a user's password on the server. The user is determined by the specified userIdentifier - which can be an email address or phone number that has already been associated with an account. Reset instructions will be sent to that identifier. This method is non-blocking.
 @param userIdentifier The email address or phone number which the account is associated with
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) passwordResetComplete:(NSError*)error {
 
        // the request was successful
        if(error == nil) {
            // do something with the user
        }
 
        else {
            // there was a problem
        }
    }
 
 */
+ (void) resetPassword:(NSString*)userIdentifier withDelegate:(id)delegate andCallback:(SEL)callback;


/** Synchronously reset a user's password on the server
 
 Reset a user's password on the server. The user is determined by the specified userIdentifier - which can be an email address or phone number that has already been associated with an account. Reset instructions will be sent to that identifier. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 @param userIdentifier The email address or phone number which the account is associated with
 */
+ (void) resetPasswordSynchronous:(NSError**)error withUserIdentifier:(NSString*)userIdentifier;


/** Synchronously verify the current user's phone number
 
 This method is used to verify the phone number of the currently logged in user. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 @param code The code which verifies the currently logged in user
 */
- (void) verifyPhoneNumber:(NSError**)error withCode:(NSString*)code;


/** Asynchronously verify the current user's phone number
 
 This method is used to verify the phone number of the currently logged in user. This is a non-blocking method.
 @param code The code which verifies the currently logged in user
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) verificationComplete:(KiiUser*)user withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
            // do something with the user
         }
         
         else {
            // there was a problem
         }
     }
 
 */
- (void) verifyPhoneNumber:(NSString*)code withDelegate:(id)delegate andCallback:(SEL)callback;


/** Synchronously resend the email verification
 
 This method will re-send the email verification to the currently logged in user. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) resendEmailVerificationSynchronous:(NSError**)error;


/** Asynchronously resend the email verification
 
 This method is used to resend the email verification for the currently logged in user. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
     
     - (void) verificationCodeReSent:(KiiUser*)user withError:(NSError*)error {
     
        // the request was successful
        if(error == nil) {
            // do something with the user
        }
     
        else {
            // there was a problem
        }
     }
     
 */
- (void) resendEmailVerification:(id)delegate andCallback:(SEL)callback;


/** Synchronously resend the phone number verification
 
 This method will re-send the SMS verification to the currently logged in user. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) resendPhoneNumberVerificationSynchronous:(NSError**)error;


/** Asynchronously resend the phone number verification
 
 This method is used to resend the phone number verification for the currently logged in user. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
     
     - (void) verificationCodeReSent:(KiiUser*)user withError:(NSError*)error {
     
        // the request was successful
        if(error == nil) {
            // do something with the user
        }
     
        else {
            // there was a problem
        }
     }
     
 */
- (void) resendPhoneNumberVerification:(id)delegate andCallback:(SEL)callback;


/** Synchronously gets a list of groups which the user is a member of
 
 This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 @return An array of KiiGroup objects
 */
- (NSArray*) memberOfGroupsSynchronous:(NSError**)error;


/** Asynchronously gets a list of groups which the user is a member of
 
 This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userIsMember:(KiiUser*)user ofGroups:(NSArray*)groups withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
 
            // do something with the user's groups
            for(KiiGroup *g in groups) {
                // do something with the group
            }
         }
         
         else {
            // there was a problem
         }
     }
 
 */
- (void) memberOfGroups:(id)delegate andCallback:(SEL)callback;

/** Get or create a bucket at the user level
 
 @param bucketName The name of the bucket you'd like to use
 @return An instance of a working KiiBucket
 */
- (KiiBucket*) bucketWithName:(NSString*)bucketName;


/** Get or create a file bucket at the user level
 
 @param bucketName The name of the file bucket you'd like to use
 @return An instance of a working KiiFileBucket
 */
- (KiiFileBucket*) fileBucketWithName:(NSString*)bucketName;


/** Asynchronously updates the local user's data with the user data on the server
 
 The user must exist on the server. Local data will be overwritten.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userRefreshed:(KiiUser*)user withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     }
     
 */
- (void) refresh:(id)delegate withCallback:(SEL)callback;


/** Synchronously updates the local user's data with the user data on the server
 
 The user must exist on the server. Local data will be overwritten. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) refreshSynchronous:(NSError**)error;


/** Asynchronously saves the latest user values to the server 
 
 The user must exist in order to make this method call. If the user does exist, the application-specific fields that have changed will be updated accordingly. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) userSaved:(KiiUser*)user withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
            // do something with the user
         }
         
         else {
            // there was a problem
         }
     }
 
 */
- (void) save:(id)delegate withCallback:(SEL)callback;


/** Synchronously saves the latest user values to the server 
 
 The user must exist in order to make this method call. If the user does exist, the application-specific fields that have changed will be updated accordingly. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) saveSynchronous:(NSError**)error;



/** Asynchronously deletes the user from the server 
 
 The user must exist on the server for this method to execute properly. This is a non-blocking method.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
    - (void) userDeleted:(KiiUser*)user withError:(NSError*)error {
     
        // the request was successful
        if(error == nil) {
            // do something with the object
        }
     
        else {
            // there was a problem
        }
    
    }
 
 */
- (void) delete:(id)delegate withCallback:(SEL)callback;


/** Synchronously deletes the user from the server
 
 The user must exist on the server for this method to execute properly. This is a blocking method.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) deleteSynchronous:(NSError**)error;


/** Prints the contents of this user to log
 
 For developer purposes only, this method prints the user in a readable format to the log for testing.
 */
- (void) describe;



/** Sets a key/value pair to a KiiUser
 
 If the key already exists, its value will be written over. If the object is of invalid type, it will return false and an NSError will be thrown (quietly). Accepted types are any JSON-encodable objects.
 @param object The value to be set. Object must be of a JSON-encodable type (Ex: NSDictionary, NSArray, NSString, NSNumber, etc)
 @param key The key to set. The key must not be a system key (created, metadata, modified, type, uuid) or begin with an underscore (_)
 @return True if the object was set, false otherwise.
 */
- (BOOL) setObject:(id)object forKey:(NSString*)key;


/** Checks to see if an object exists for a given key
 
 @param key The key to check for existence
 @return True if the object exists, false otherwise.
 */
- (BOOL) hasObject:(NSString*)key;


/** Removes a specific key/value pair from the object
 If the key exists, the key/value will be removed from the object. Please note that the object must be saved before the changes propogate to the server.
 @param key The key of the key/value pair that will be removed
 */
- (void) removeObjectForKey:(NSString*)key;


/** Gets the value associated with the given key
 
 @param key The key to retrieve
 @return An object if the key exists, null otherwise
 */
- (id) getObjectForKey:(NSString*)key;


/** Updates the user's email address on the server
 
 This is a non-blocking method.
 @param newEmail The new email address to change to
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) emailChanged:(KiiUser*)user withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     
     }
 **/
- (void) changeEmail:(NSString*)newEmail withDelegate:(id)delegate andCallback:(SEL)callback;


/** Updates the user's email address on the server
 
 This is a blocking method.
 @param newEmail The new email address to change to
 @param error An NSError object, set to nil, to test for errors
 **/
- (void) changeEmailSynchronous:(NSString*)newEmail withError:(NSError**)error;


/** Updates the user's phone number on the server
 
 This is a non-blocking method.
 @param newPhoneNumber The new phone number to change to
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) phoneChanged:(KiiUser*)user withError:(NSError*)error {
     
         // the request was successful
         if(error == nil) {
             // do something with the user
         }
         
         else {
             // there was a problem
         }
     
     }
 **/
- (void) changePhone:(NSString*)newPhoneNumber withDelegate:(id)delegate andCallback:(SEL)callback;


/** Updates the user's phone number on the server
 
 This is a blocking method.
 @param newPhoneNumber The new phone number to change to
 @param error An NSError object, set to nil, to test for errors
 **/
- (void) changePhoneSynchronous:(NSString*)newPhoneNumber withError:(NSError**)error;


/** Logs the currently logged-in user out of the KiiSDK */
+ (void) logOut;


/** Determines whether or not there is a KiiUser currently logged in
 @return TRUE if an authenticated user exists, FALSE otherwise
 */
+ (BOOL) loggedIn;


/** Get the currently logged-in user
 @return A KiiUser object representing the current user, nil if no user is logged-in
 */
+ (KiiUser*) currentUser;


@end
