/*jslint node: true */
'use strict';

var Benchmark = require('benchmark');
var murmurhash3 = require('murmurhash3');
var xxhash = require('xxhash');
var farmhash = require('../index');

var randomInteger = function() {
  return Math.floor(Math.random() * 2147483647);
};

var randomStringOfLength = function(length) { 
  var str = '';
  while (str.length < length) {
    str = str + Math.random().toString(36).slice(2);
  }
  return str.slice(0, length);
};

// Test 1

(function() {
  console.log('Test seed collisions (same key, different seeds)');

  var input = randomStringOfLength(100);
  var inputBuffer = new Buffer(input); // xxhash
  console.log('Using input of length ' + input.length);
  var iterations = 1000000;
  console.log('Using ' + iterations + ' iterations');

  var hashes = {
    murmurhash3: {},
    xxhash: {},
    farmhash: {}
  };
  var collisions = {
    murmurhash3: 0,
    xxhash: 0,
    farmhash: 0
  };
  for (var seed = 0; seed < iterations; seed++) {
    var murmur = murmurhash3.murmur32Sync(input, seed);
    if (murmur in hashes.murmurhash3) {
      collisions.murmurhash3++;
    } else {
      hashes.murmurhash3[murmur] = true;
    }
    var xx = xxhash.hash(inputBuffer, seed);
    if (xx in hashes.xxhash) {
      collisions.xxhash++;
    } else {
      hashes.xxhash[xx] = true;
    }
    var farm = farmhash.hash32WithSeed(input, seed);
    if (farm in hashes.farmhash) {
      collisions.farmhash++;
    } else {
      hashes.farmhash[farm] = true;
    }
  }
  console.log('Collisions:');
  console.dir(collisions);
  console.log();
})();

// Test 2

(function() {
  console.log('Test key collisions (same seed, different keys)');

  var seed = randomInteger();
  console.log('Using seed ' + seed);
  var keyLength = 100;
  console.log('Using key length of ' + keyLength);
  var iterations = 1000000;
  console.log('Using ' + iterations + ' iterations');

  var hashes = {
    murmurhash3: {},
    xxhash: {},
    farmhash: {}
  };
  var collisions = {
    murmurhash3: 0,
    xxhash: 0,
    farmhash: 0
  };
  for (var i = 0; i < iterations; i++) {
    var input = randomStringOfLength(keyLength);
    var inputBuffer = new Buffer(input); // xxhash

    var murmur = murmurhash3.murmur32Sync(input, seed);
    if (murmur in hashes.murmurhash3) {
      collisions.murmurhash3++;
    } else {
      hashes.murmurhash3[murmur] = true;
    }
    var xx = xxhash.hash(inputBuffer, seed);
    if (xx in hashes.xxhash) {
      collisions.xxhash++;
    } else {
      hashes.xxhash[xx] = true;
    }
    var farm = farmhash.hash32WithSeed(input, seed);
    if (farm in hashes.farmhash) {
      collisions.farmhash++;
    } else {
      hashes.farmhash[farm] = true;
    }
  }
  console.log('Collisions:');
  console.dir(collisions);
  console.log();
})();

// Test 3

(function() {
  console.log('Test key length performance');

  var seed = randomInteger();
  console.log('Using seed ' + seed);

  [100, 1000, 10000].forEach(function(length) {

    var input = randomStringOfLength(length);
    var inputBuffer = new Buffer(input); // xxhash
    console.log('Using key of length ' + length);

    (new Benchmark.Suite())
    .add('murmurhash3', function() {
      murmurhash3.murmur32Sync(input);
    })
    .add('murmurhash3+seed', function() {
      murmurhash3.murmur32Sync(input, seed);
    })
    .add('farmhash-hash-switch-string', function() {
      farmhash.hash32(input);
    })
    .add('farmhash-hash-switch-buffer', function() {
      farmhash.hash32(inputBuffer);
    })
    .add('farmhash-hash-buffer-only', function() {
      farmhash.hash32Buffer(inputBuffer);
    })
    .add('farmhash-hash-string-only', function() {
      farmhash.hash32String(input);
    })
    .add('farmhash-hash+seed-switch-string', function() {
      farmhash.hash32WithSeed(input, seed);
    })
    .add('farmhash-hash+seed-switch-buffer', function() {
      farmhash.hash32WithSeed(inputBuffer, seed);
    })
    .add('farmhash-hash+seed-string-only', function() {
      farmhash.hash32WithSeedString(input, seed);
    })
    .add('farmhash-hash+seed-buffer-only', function() {
      farmhash.hash32WithSeedBuffer(inputBuffer, seed);
    })
    .add('farmhash-fingerprint', function() {
      farmhash.fingerprint32(input);
    })
    .add('xxhash+seed', function() {
      xxhash.hash(inputBuffer, seed);
    })
    .on('cycle', function(event) {
      console.log(String(event.target));
    }).run();

  });
})();
