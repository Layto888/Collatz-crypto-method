# Collatz-crypto-method
Collatz encoding method with wide format characters.

# Description: 

Originally based on Caesar's encryption, but instead of having a key 'D' with fixed offset.
Encryption by this method use a variable C key offset witch is depending of the previous C value.

The values ​​of C are determined by collatz's sequence. Aka: syracuse conjecture (Cf. see the wiki)
The starting value given to the sequence, is the secret encryption and decryption Key.

     * NB: We take the table of the extended ascii.

 * Example:

            C = 15 ->  is the start offset value.
            The sequence C = 15 -> 46 -> 23 -> 70 -> 35 ... etc. Are the offset values for each char.


* @param std-c99.
* NDEBUG is undefined in relase mode for assertions.
* @author A.Amine
* @date  02/04/2017



# Example of output file :

* Clear -> Atbash encryption:

Gsrh rh z hrnkov gvhg uli Xloozga hvjfvmxv xibkgl nvgslwv xlnyrmvw drgs zgyzhs nvgslwv 
FKKVI GVHGV WLMV zmw mld mfnyvih 9876543210 zmw hlnv hkvxrzo xszih : ?!;,<>²&éè'()-_- ç ~ ^ @[]{}+-*/.= % µ *@^
zmw mld ivk : 8888888888888888888888888888888888888888888888888888 9999999999999999999999999999999999999999999

* Atbash -> Collatz encryption with (207) non-printable characters:

ëÅ=ëÕiW•©;°@Ç‰ªéÔ{v7-°4§Îˆ…y©óó!le=SöëèÀYå±1v ÓžÛAËGíè±,¡èUãñÆ’]3p„{k\ÉmsN9¼'Û½¢2éäóÄ¯5©=ÅMäÎY6Ÿ^DçŸ¸·–U‚ìa®‰q2´·1µ+«ŸÇz“¯	=¦ÅKÚ¡ÎyC“„F-å›ÏÈuºÓÊ:œOv¹=;¯ó½Ôº”Èü„ÂÙ"Í01ÈYÅ«ÑÃ:Ì!`5½@ùæƒe]—GE?='¹IKqÃ»£kÑå3	‰ÅÁµ¡uß±…!ÑõsÉÍé?-“KqÓûe¯õœdš>HV€

* Collatz encryption -> Clear (original message):

This is a simple test for Collatz sequence crypto methode combined with atbash methode 
UPPER TESTE DONE and now numbers 0123456789 and some special chars : ?!;,<>²&éè'()-_- ç ~ ^ @[]{}+-*/.= % µ *@^
and now rep : 1111111111111111111111111111111111111111111111111111 0000000000000000000000000000000000000000000

