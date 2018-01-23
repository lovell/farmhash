'use strict';

const Benchmark = require('benchmark');
const murmurhash3 = require('murmurhash3');
const xxhash = require('xxhash');
const farmhash = require('../index');

function randomInteger () {
  return Math.floor(Math.random() * 2147483647);
}

function randomStringOfLength (length) {
  let str = '';
  while (str.length < length) {
    str = str + Math.random().toString(36).slice(2);
  }
  return str.slice(0, length);
}

// Test 1

(function () {
  console.log('Test seed collisions (same key, different seeds)');

  const input = randomStringOfLength(100);
  const inputBuffer = Buffer.from(input); // xxhash
  console.log('Using input of length ' + input.length);
  const iterations = 1000000;
  console.log('Using ' + iterations + ' iterations');

  const hashes = {
    murmurhash3: {},
    xxhash: {},
    farmhash: {}
  };
  const collisions = {
    murmurhash3: 0,
    xxhash: 0,
    farmhash: 0
  };
  for (let seed = 0; seed < iterations; seed++) {
    const murmur = murmurhash3.murmur32Sync(input, seed);
    if (murmur in hashes.murmurhash3) {
      collisions.murmurhash3++;
    } else {
      hashes.murmurhash3[murmur] = true;
    }
    const xx = xxhash.hash(inputBuffer, seed);
    if (xx in hashes.xxhash) {
      collisions.xxhash++;
    } else {
      hashes.xxhash[xx] = true;
    }
    const farm = farmhash.hash32WithSeed(input, seed);
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

(function () {
  console.log('Test key collisions (same seed, different keys)');

  const seed = randomInteger();
  console.log('Using seed ' + seed);
  const keyLength = 100;
  console.log('Using key length of ' + keyLength);
  const iterations = 1000000;
  console.log('Using ' + iterations + ' iterations');

  const hashes = {
    murmurhash3: {},
    xxhash: {},
    farmhash: {}
  };
  const collisions = {
    murmurhash3: 0,
    xxhash: 0,
    farmhash: 0
  };
  for (let i = 0; i < iterations; i++) {
    const input = randomStringOfLength(keyLength);
    const inputBuffer = Buffer.from(input); // xxhash

    const murmur = murmurhash3.murmur32Sync(input, seed);
    if (murmur in hashes.murmurhash3) {
      collisions.murmurhash3++;
    } else {
      hashes.murmurhash3[murmur] = true;
    }
    const xx = xxhash.hash(inputBuffer, seed);
    if (xx in hashes.xxhash) {
      collisions.xxhash++;
    } else {
      hashes.xxhash[xx] = true;
    }
    const farm = farmhash.hash32WithSeed(input, seed);
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

(function () {
  console.log('Test key length performance');

  const seed = randomInteger();
  const seed2 = randomInteger();
  console.log('Using seed ' + seed);

  [100, 1000, 10000].forEach(function (length) {
    const input = randomStringOfLength(length);
    const inputBuffer = Buffer.from(input); // xxhash
    console.log('Using key of length ' + length);

    (new Benchmark.Suite())
      .add('murmurhash3', function () {
        murmurhash3.murmur32Sync(input);
      })
      .add('murmurhash3+seed', function () {
        murmurhash3.murmur32Sync(input, seed);
      })
      .add('farmhash-hash32-string', function () {
        farmhash.hash32(input);
      })
      .add('farmhash-hash32-buffer', function () {
        farmhash.hash32(inputBuffer);
      })
      .add('farmhash-hash32+seed-string', function () {
        farmhash.hash32WithSeed(input, seed);
      })
      .add('farmhash-hash32+seed-buffer', function () {
        farmhash.hash32WithSeed(inputBuffer, seed);
      })
      .add('farmhash-fingerprint32-string', function () {
        farmhash.fingerprint32(input);
      })
      .add('farmhash-fingerprint32-buffer', function () {
        farmhash.fingerprint32(inputBuffer);
      })
      .add('farmhash-fingerprint64-string', function () {
        farmhash.fingerprint64(input);
      })
      .add('farmhash-fingerprint64-buffer', function () {
        farmhash.fingerprint64(inputBuffer);
      })
      .add('farmhash-hash64-string', function () {
        farmhash.hash64(input);
      })
      .add('farmhash-hash64-buffer', function () {
        farmhash.hash64(inputBuffer);
      })
      .add('farmhash-hash64+seed-string', function () {
        farmhash.hash64WithSeed(input, seed);
      })
      .add('farmhash-hash64+seed-buffer', function () {
        farmhash.hash64WithSeed(inputBuffer, seed);
      })
      .add('farmhash-hash64+seeds-string', function () {
        farmhash.hash64WithSeeds(input, seed, seed2);
      })
      .add('farmhash-hash64+seeds-buffer', function () {
        farmhash.hash64WithSeeds(inputBuffer, seed, seed2);
      })
      .add('xxhash+seed', function () {
        xxhash.hash(inputBuffer, seed);
      })
      .on('cycle', function (event) {
        console.log(String(event.target));
      }).run();
  });
})();
