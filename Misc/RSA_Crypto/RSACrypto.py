import binascii

#n = 0x367198D6B5614E95813ADD8F22A4717BC72BE1EABD933D1B86944FDB75B8ED230BE62D7D1B69D222095C128C86F82012ECB116191FD9D018A6D02F84DB27BC51A21307DC86F4BF771C691C143E5ABE549B5BD2D6EB1A21FD6270E7E1B48FE0611FBB2E1B0B3524E6F4DE8B4E4A345DA44A13DE825B72608DB6C7C4A40B78266E6C87BBFDEF6B48381D49C4507A58BCD47B76D64B45908B158BD7EBC4DACB0B1CFD6C2C19574F40EB2EFD0E9E10DC7005CAD39BCAF52B9EAC3873368D69031C5E724684A44F068EFD1D3DC096D9B5D6411E58BDEE43E46B99A0D0494B9DB28195AF901AFF130D4A6E203DAD08DA57FA7E40262A5BADB2A323EDA28B44696AB305D
#d = 4221909016509078129201801236879446760697885220928506696150646938237440992746683409881141451831939190609743447676525325543963362353923989076199470515758399L
#c = 0x1e04304936215de8e21965cfca9c245b1a8f38339875d36779c0f123c475bc24d5eef50e7d9ff5830e80c62e8083ec55f27456c80b0ab26546b9aeb8af30e82b650690a2ed7ea407dcd094ab9c9d3d25a93b2140dcebae1814610302896e67f3ae37d108cd029fae6362ea7ac1168974c1a747ec9173799e1107e7a56d783660418ebdf6898d7037cea25867093216c2c702ef3eef71f694a6063f5f0f1179c8a2afe9898ae8dec5bb393cdffa3a52a297cd96d1ea602309ecf47cd009829b44ed3100cf6194510c53c25ca7435f60ce5f4f614cdd2c63756093b848a70aade002d6bc8f316c9e5503f32d39a56193d1d92b697b48f5aa43417631846824b5e86

m = hex(pow(c,d,n)).rstrip("L")
print m
print binascii.unhexlify(m[2:])




