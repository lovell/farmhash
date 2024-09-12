import farmhash from '.';

const testString: string = 'test';
const testBuffer: Buffer = Buffer.from(testString);
const testSeed1: number = 1;
const testSeed2: number = 2;

const f32s: number = farmhash.fingerprint32(testString);
const f32b: number = farmhash.fingerprint32(testBuffer);

const f64s: bigint = farmhash.fingerprint64(testString);
const f64b: bigint = farmhash.fingerprint64(testBuffer);

const f64ss: bigint = farmhash.fingerprint64signed(testString);
const f64sb: bigint = farmhash.fingerprint64signed(testBuffer);

const h32s: number = farmhash.hash32(testString);
const h32b: number = farmhash.hash32(testBuffer);

const h32ss: number = farmhash.hash32WithSeed(testString, testSeed1);
const h32sb: number = farmhash.hash32WithSeed(testBuffer, testSeed1);

const h64s: bigint = farmhash.hash64(testString);
const h64b: bigint = farmhash.hash64(testBuffer);

const h64ss: bigint = farmhash.hash64WithSeed(testString, testSeed1);
const h64sb: bigint = farmhash.hash64WithSeed(testBuffer, testSeed1);

const h64sss: bigint = farmhash.hash64WithSeeds(testString, testSeed1, testSeed2);
const h64ssb: bigint = farmhash.hash64WithSeeds(testBuffer, testSeed1, testSeed2);
