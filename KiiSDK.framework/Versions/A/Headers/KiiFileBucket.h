//
//  KiiFileBucket.h
//  KiiSDK-Private
//
//  Created by Chris Beauchamp on 6/6/12.
//  Copyright (c) 2012 Chris Beauchamp. All rights reserved.
//

#import <Foundation/Foundation.h>

@class KiiFile, KiiUser, KiiQuery, KiiACL;

/** A reference to a bucket within a user's scope which contains KiiFile objects */
@interface KiiFileBucket : NSObject 


/** Get the ACL handle for this bucket. Any KiiACLEntry objects added or revoked from this ACL object will be appended to/removed from the server on ACL save. */
@property (readonly) KiiACL *bucketACL;


/** Create a KiiFile within the current bucket based on the given local path
 
 The object will not be created on the server until the KiiFile is explicitly saved. This method returns a working KiiFile with local attributes pre-filled. For empty file creation, the -file method is also available.
 @param filePath The path of the file to use
 @return An empty KiiObject with the specified type
 */
- (KiiFile*) fileWithLocalPath:(NSString*)filePath;


/** Create a KiiFile within the current bucket
 
 The file will not be created on the server until the KiiFile is explicitly saved. This method simply returns an empty working KiiFile.
 @return An empty KiiFile
 */
- (KiiFile*) file;


/** Execute a query on the current bucket
 
 The query will be executed against the server, returning a result set. This is a blocking method
 @param query The query to execute
 @param error An NSError object, set to nil, to test for errors
 @return An NSArray of objects returned by the query
 */
- (NSArray*) executeQuerySynchronous:(KiiQuery*)query withError:(NSError**)error;


/** Execute a query on the current bucket
 
 The query will be executed against the server, returning a result set. This is a non-blocking method
 @param query The query to execute
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) queryFinished:(KiiQuery*)query onBucket:(KiiFileBucket*)bucket withResults:(NSArray*)results andError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
         
             // do something with the results
             for(KiiObject *o in results) {
                // use this object
             }
         }
         
         else {
            // there was a problem
         }
     }
 
 */
- (void) executeQuery:(KiiQuery*)query withDelegate:(id)delegate andCallback:(SEL)callback;


/** Synchronously deletes a file bucket from the server.
 
 Delete a file bucket from the server. This method is blocking.
 @param error An NSError object, set to nil, to test for errors
 */
- (void) deleteSynchronous:(NSError**)error;


/** Asynchronously deletes a file bucket from the server.
 
 Delete a file bucket from the server. This method is non-blocking.
 @param delegate The object to make any callback requests to
 @param callback The callback method to be called when the request is completed. The callback method should have a signature similar to:
 
     - (void) bucketDeleted:(KiiFileBucket*)bucket withError:(NSError*)error {
         
         // the request was successful
         if(error == nil) {
             // do something
         }
         
         else {
             // there was a problem
         }
     }
 
 */
- (void) delete:(id)delegate withCallback:(SEL)callback;


@end
