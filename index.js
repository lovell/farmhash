/*jslint node: true */
'use strict';

var farmhash = require('./build/Release/farmhash');

module.exports.Hash64 = function(str) {
  if (typeof str !== 'string') {
    throw new Error('Expected a string');
  }
  return farmhash.Hash64(str);
};
