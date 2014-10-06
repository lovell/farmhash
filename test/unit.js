/*jslint node: true */
'use strict';

var assert = require('assert');
var farmhash = require('../index');

var theQuickBrownFox = 'The quick brown fox jumped over the lazy sleeping dog';

var hash = farmhash.Hash64(theQuickBrownFox);
assert.strictEqual(true, /^[0-9]{1,21}$/.test(hash));
