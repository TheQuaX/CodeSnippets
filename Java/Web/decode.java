byte[] decoded = new byte[6];
byte[] encoded = new byte[] {198, 131, 130, 182, 194, 135};
byte[] key = byte[4] {167, 225, 225, 210};

for (int i = 0; i < encoded.length; i++) {
    decoded[i] = (byte)(encoded[i] ^ key[i & 0x3]);
}