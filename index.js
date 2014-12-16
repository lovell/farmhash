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
    verifyStringOrBuffer(input);
    return farmhash.Hash32(input);
  },
  hash32Buffer: function(input) {
    verifyBuffer(input);
    return farmhash.Hash32Buffer(input);
  },
  hash32String: function(input) {
    verifyString(input);
    return farmhash.Hash32String(input);
  },
  hash32WithSeed: function(input, seed) {
    verifyStringOrBuffer(input);
    verifyInteger(seed);
    return farmhash.Hash32WithSeed(input, seed);
  },
  hash32WithSeedString: function(input, seed) {
    verifyString(input);
    verifyInteger(seed);
    return farmhash.Hash32WithSeedString(input, seed);
  },
  hash32WithSeedBuffer: function(input, seed) {
    verifyBuffer(input);
    verifyInteger(seed);
    return farmhash.Hash32WithSeedBuffer(input, seed);
  },
  hash64: function(input) {
    verifyString(input);
    return farmhash.Hash64(input);
  },
  hash64WithSeed: function(input, seed) {
    verifyString(input);
    verifyInteger(seed);
    return farmhash.Hash64WithSeed(input, seed);
  },
  hash64WithSeeds: function(input, seed1, seed2) {
    verifyString(input);
    verifyInteger(seed1);
    verifyInteger(seed2);
    return farmhash.Hash64WithSeeds(input, seed1, seed2);
  },

  // Fingerprint methods - platform independent
  fingerprint32: function(input) {
    verifyString(input);
    return farmhash.Fingerprint32(input);
  },
  fingerprint64: function(input) {
    verifyString(input);
    return farmhash.Fingerprint64(input);
  }

};
