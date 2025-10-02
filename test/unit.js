const assert = require('node:assert');
const farmhash = require('../index');

const input = 'The quick brown fox jumped over the lazy sleeping dog';
const seed = 123;

// hash32 - valid
const hash32 = farmhash.hash32(input);
assert.strictEqual('number', typeof hash32);
assert.strictEqual(true, hash32 > 0);

// hash32 - invalid
assert.throws(() => {
  farmhash.hash32(seed);
});

// hash32WithSeed - valid
const hash32WithSeed = farmhash.hash32WithSeed(input, seed);
assert.strictEqual('number', typeof hash32WithSeed);
assert.strictEqual(true, hash32WithSeed > 0);

// hash32WithSeed - invalid
assert.throws(() => {
  farmhash.hash32WithSeed(input);
});
assert.throws(() => {
  farmhash.hash32WithSeed(seed, seed);
});
assert.throws(() => {
  farmhash.hash32WithSeed(input, input);
});

// hash64 - valid
const hash64 = farmhash.hash64(input);
assert.strictEqual('bigint', typeof hash64);
assert.strictEqual(true, /^[0-9]{1,20}$/.test(hash64.toString()));

// hash64 - invalid
assert.throws(() => {
  farmhash.hash64(seed);
});

// hash64WithSeed - valid
const hash64WithSeed = farmhash.hash64WithSeed(input, seed);
assert.strictEqual('bigint', typeof hash64WithSeed);
assert.strictEqual(true, /^[0-9]{1,20}$/.test(hash64WithSeed.toString()));

// hash64WithSeed - invalid
assert.throws(() => {
  farmhash.hash64WithSeed(input);
});
assert.throws(() => {
  farmhash.hash64WithSeed(seed, seed);
});
assert.throws(() => {
  farmhash.hash32WithSeed(input, input);
});

// hash64WithSeeds - valid
const hash64WithSeeds = farmhash.hash64WithSeeds(input, seed, seed);
assert.strictEqual('bigint', typeof hash64WithSeeds);
assert.strictEqual(true, /^[0-9]{1,20}$/.test(hash64WithSeeds.toString()));

// hash64WithSeeds - invalid
assert.throws(() => {
  farmhash.hash64WithSeeds(input);
});
assert.throws(() => {
  farmhash.hash64WithSeeds(input, seed);
});
assert.throws(() => {
  farmhash.hash64WithSeeds(input, input, input);
});
assert.throws(() => {
  farmhash.hash64WithSeeds(seed, seed, seed);
});

// fingerprint32 - valid
const fingerprint32 = farmhash.fingerprint32(input);
assert.strictEqual('number', typeof fingerprint32);
assert.strictEqual(2280764877, fingerprint32);

// fingerprint32 - invalid
assert.throws(() => {
  farmhash.fingerprint32(seed);
});

// fingerprint64 - valid
const fingerprint64 = farmhash.fingerprint64(input);
assert.strictEqual('bigint', typeof fingerprint64);
assert.strictEqual('17097846426514660294', fingerprint64.toString());

// https://github.com/lovell/farmhash/issues/26
assert.strictEqual(
  '16905089972579912905',
  farmhash.fingerprint64('1footrue').toString(),
);
assert.strictEqual(
  '-1541654101129638711',
  farmhash.fingerprint64signed('1footrue').toString(),
);

// fingerprint64 - invalid
assert.throws(() => {
  farmhash.fingerprint64(seed);
});
