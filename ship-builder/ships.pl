
# builders:
# B bilstein
# C clan severn
# D delta research
# G general products
# L ling-standard
# M makhidkarun
# U unknown
# V vlandian 
# Z zirunkarish

# feature flags:
# 0x0001 advanced sensors
# 0x0002 repair drones
# 0x0004 stealth tech
# 0x0008 black globe
# 0x0010 etc

open my $out, '>:raw', 'SHIPS.BIN';
print $out pack 'xx';  # initial commodore bytes
foreach (<DATA>)
{
   my ($qsp1, $m, $j, $builder, $tl1, $tl, $f1, $f2, $flags, $cargo, $pass, $low, $ar, $mcr1, $mcr, $status, $hex1, $name) = split ' ', $_, 18;
   chomp $name;

   my $engines = $j + ($m << 4);
   my $jfuel   = $f2 + ($f1 << 4);
   
   print $out pack('A6a13x', $qsp1 . $m . $j, uc $name),
              pack('ca',   $tl, $builder),
			  pack('cc',   $engines, $jfuel),
			  pack('cccc', $cargo, $pass, $low, $ar),
			  pack('c',    int($mcr/10)), # max = MCR 2550
			  pack('c',    $status),
			  pack('xx');  # hex location unknown

}
close $out;

`cp SHIPS.BIN ../src`;
`cp SHIPS.BIN ../util`;

#          Builder   Fuel             Armor     Status
#          |         |                |         |
# QSP      B    TL   F F ff   payload A  mcr    S Hex classname
#                        |
#                        feature flags
__DATA__
ABU 1 1  G  TL 10  1 1 ..  82 06 20 10 MCr 50  1 HH  beowulf
SAL 2 2  V  TL 10  2 2 ..   3 03 00 10 MCr 52  1 HH  murphy
SAA 2 2  D  TL 10  2 2 ..   3 03 00 20 MCr 60  1 HH  serpent
CDB 3 3  Z  TL 12  3 3 ..  43 04 10 36 MCr 140 1 HH  enforcer
RDA 1 1  M  TL 10  1 1 .. 200 08 09 10 MCr 90  1 HH  akkigish
PDA 4 2  U  TL 12  2 2 ..  40 00 20 24 MCr 150 1 HH  nishemani
EEA 4 3  L  TL 14  3 3 ..  10 02 02 42 MCr 310 1 HH  lurushaar k.
VKU 6 4  C  TL 15  4 4 ..  10 08 10 60 MCr 650 1 HH  chrysanthemum
TMA 5 H  D  TL 17  1 1 .. 500 20 00 17 MCr 530 1 HH  orca
