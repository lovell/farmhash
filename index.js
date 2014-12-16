/*jslint node: true */
'use strict';

var farmhash = require('./build/Release/farmhash');

// Input validation

var verifyString = function(input) {
  if (typeof input !== 'string') {
    throw new Error('Expected a string for input');
  }
};
var verifyStringOrBuffer = function(input) {
  if (typeof input !== 'string' && !Buffer.isBuffer(input)) {
    throw new Error('Expected a String of Buffer for input');
  }
};
var verifyInteger = function(input) {
  if (typeof input !== 'number' || (input % 1) !== 0) {
    throw new Error('Expected an integer for seed');
  }
};
var verifyBuffer = function(input) {
  if (! Buffer.isBuffer(input)) {
    throw new Error('Expected a Buffer for input');
  }
};

module.exports = {

  // Hash methods - platform dependent
  hash32: function(input) {
    if (typeof input === 'string') {
      return farmhash.Hash32String(input);
    }
    if (Buffer.isBuffer(input)) {
      return farmhash.Hash32Buffer(input);
    }
    throw new Error('Expected a String or Buffer for input');
  },
  hash32WithSeed: function(input, seed) {
    verifyInteger(seed);
    if (typeof input === 'string') {
      return farmhash.Hash32WithSeedString(input, seed);
    }
    if (Buffer.isBuffer(input)) {
      return farmhash.Hash32WithSeedBuffer(input, seed);
    }
    throw new Error('Expected a String or Buffer for input');
  },
  hash64: function(input) {
    if (typeof input === 'string') {
      return farmhash.Hash64String(input);
    }
    if (Buffer.isBuffer(input)) {
      return farmhash.Hash64Buffer(input);
    }
    throw new Error('Expected a String or Buffer for input');
    return farmhash.Hash64(input);
  },
  hash64WithSeed: function(input, seed) {
    verifyInteger(seed);
    if (typeof input === 'string') {
      return farmhash.Hash64WithSeedString(input, seed);
    }
    if (Buffer.isBuffer(input)) {
      return farmhash.Hash64WithSeedBuffer(input, seed);
    }
    throw new Error('Expected a String or Buffer for input');
  },
  hash64WithSeeds: function(input, seed1, seed2) {
    verifyInteger(seed1);
    verifyInteger(seed2);
    if (typeof input === 'string') {
      return farmhash.Hash64WithSeedsString(input, seed1, seed2);
    }
    if (Buffer.isBuffer(input)) {
      return farmhash.Hash64WithSeedsBuffer(input, seed1, seed2);
    }
    throw new Error('Expected a String or Buffer for input');
  },

  // Fingerprint methods - platform independent
  fingerprint32: function(input) {
    if (typeof input === 'string') {
      return farmhash.Fingerprint32String(input);
    }
    if (Buffer.isBuffer(input)) {
      return farmhash.Fingerprint32Buffer(input);
    }
    throw new Error('Expected a String or Buffer for input');
  },
  fingerprint64: function(input) {
    if (typeof input === 'string') {
      return farmhash.Fingerprint64String(input);
    }
    if (Buffer.isBuffer(input)) {
      return farmhash.Fingerprint64Buffer(input);
    }
  }
};
