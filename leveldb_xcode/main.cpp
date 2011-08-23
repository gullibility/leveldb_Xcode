/*
 *  main.cpp
 *  leveldb_xcode
 *
 *  Created by Ryan Chen on 8/12/11.
 *  Copyright 2011 Homebrew Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#include "leveldb/db.h"

int main (int argc, const char * argv[]) {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
    // insert code here...
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
	assert(status.ok());
	
	std::string value1;
	std::string value2;
	leveldb::Slice s1 = "hello";
	leveldb::Slice s2 = "world";
	
	leveldb::ReadOptions readOption;
	leveldb::WriteOptions writeOption;
	leveldb::Status s = db->Put(writeOption, s1, s2);
	if (s.ok()) s = db->Get(readOption, s1, &value1);
	
	printf("v:%s\n", value1.c_str());
	
	if (s.ok()) s = db->Delete(writeOption, s1);
	
	if (s.ok()) s = db->Get(readOption, s1, &value1);
	
	printf("end:%s\n", value1.c_str());
	
	delete db;
    [pool drain];
    return 0;
}

