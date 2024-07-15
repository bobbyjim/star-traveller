
open my $out, '>:raw', 'SHIPS.BIN';
#print $out pack 'xx';  # initial commodore bytes
foreach (<DATA>)
{
   # Al  Name            QSP     AV    B  Br F  Payloads   MCr    Turrets
   my ($allegiance, $name, $qsp, $av, $builder, $bridge, $flags, $cargo, $pass, $low, $mcr, @turrets) = split ' ';

   next unless $name;

   chomp $name;
   $name =~ s/-/ /;

   my ($m,$j) = $qsp =~ /^.-..(.)(.)/;
   my $drives   = $j + ($m << 4);
   my $features = $bridge + ($featureFlags << 2);
   
   print $out 
            pack('a15x',    uc $name),
            pack('ccc',     $drives, $features, $av),
            pack('a6x',     uc $qsp),
			   pack('cccc',    uc $builder, $cargo, $pass, $low),
			   pack('c2x',     uc $allegiance),
			   pack('c',       int($mcr/10)), # max = MCR 2550
            pack('c*',      255,255,255,255,255,255)
            ;

   for (1..8)
   {
      $_ = shift @turrets;

      my $num = 0;         # bits 0,1,2 = emplacement type
      $num = 1 if /T1/;
      $num = 2 if /T2/;
      $num = 3 if /T3/;
      $num = 4 if /B1/;
      $num = 5 if /B2/;
      $num = 6 if /B\D/;
      $num = 7 if /LB/;

      my $deviceType = 0;  # bits 3,4 = device class.  0 = weapon.

      my $dev = 0;         # bits 5,6,7 = device.
      $dev = 1 if /L$/;    # laser
      $dev = 2 if /M$/;    # missile
      $dev = 3 if /S$/;    # sand
      $dev = 4 if /A$/;    # particle accel
      # $dev = 5 if  ?
      # $dev = 6 if  ?
      # $dev = 7 if  ?
      
      $num += $dev << 5;

      print $out pack('c', $num);
   }
}
close $out;

`cp SHIPS.BIN ../src`;
`cp SHIPS.BIN ../util`;

################################################################
#  MISSION CODES
#
#  There is NO MORE THAN THIRTY TWO mission codes.  
#  This limitation balances NPC ship variety with quantity.
#
#  MILITARY CODES:   C,E,G,P ships have 1 hardpoint per 100 tons, and have screens.
#  YACHTS:           K and Y ships have 1 hardpoint per 200 tons, round down.
#  All other craft only have 1 hardpoint per 200 tons, but at least 2 hardpoints.
#
################################################################
# BUILDERS
#
# B bilstein               C clan severn              D delta research
# E                        F                          G general products
# L ling-standard          M makhidkarun              N naellugz (vargr)
# S Osyayeao (aslan)       T tlezhveda (joe)          U unknown
# V vlandian               W                          X oxal (droyne)
# Y                        Z zirunkarish

################################################################
# FEATURE FLAGS
#
# #1 black globe
# #2 stealth coating
# #4 advanced sensors

#                             Builder  Bridge
# Allegiance                        |  |  Flags
# |                                 |  |  |
# Al  Name            QSP     AV    B  Br F  Payloads   MCr    Turrets
__DATA__
  Im	Beowulf	       A-BS11	10	   g  2	0	82	6	20	  50	   T1/0 T1/0
  Dr	Loskay	       A-CA22	12		x  1	0	55	12	9	  103	   T2/L T2/S
  Im	Sunfish	       A-CL22	15		c  1	0	70	8	8	  116    T2/S T2/M	T2/L
  Im  Long-Liner      F-KS13	12		g  1	0	417 12 10  230	   T2/L	T2/L	T2/L
  Im	Glimmerdrift	 M-FU13	12		m  1	0	124 21 80  137	   T1/0 T1/0 T1/0
  Im	Akkigish	       R-DA11	11		g  1	0	200 8	9	  90     T1/0  T1/0
  Im	Orca	          R-MA54	34		u  2	1	500 18 0	  526	   T3/L T3/M T3/S
  Im	Leviathan	    R-TU43	24		b  2	0	300 8	16	  750	   T3/L	T3/L  T3/L	T3/M	T3/M	T3/M  T3/S	T3/S	T3/S
  Im  Ishillek        U-EA42	24		b  2	0	80	12	8	  200    T3/0
  Im	Shumshuga	    W-AU11	10		g  0  0	70	0	0	  37     T1/0

  Im	Leaping-Snowcat K-BA12	11		m  2	0	6	6	4	  80	   T2/0
  Im  Sunflower       Y-EU42  8     b  2  0  20 9  0    200    T1/0 T1/0

  Im	Enforcer	       C-DB33	36		l  2	0	5	4	10	  135	   T3/M T3/M	T3/L	T3/L
  Im	Broadsword      C-HU33	24		l  2	0	50	12	0	  300    B2/0 B2/0 T3/0 T3/0 T3/0 T3/0
  Zh	Vlezhdatl       C-VS42	140	t	2	0	90	1	0	  1060	B/A	B2/M	B2/M	B1/S	B1/S	B1/L	B1/L	B1/L
  Im  Gazelle         E-DU44  56    l  2  0  0  0  0    275    B1/A  T3/M  T3/S  T3/L
  Im	Patrol-Frigate  G-EA53	26		l  2	0	20	0	0	  240	   B1/A	B1/M	B3/L	B3/L
  Zh	Shivva          G-FU24	26		t  2	0	24	0	0	  320	   B1/M	B1/S	B1/L
  As	Khosaa	       G-DL71	42		s  2	0	0	1	0	  276	   B1/A	B1/A	B1/S B1/M
  Va	Az-Alrrak	    P-DA42	24		u  2	0	15	1	12	  380	   T3/L	T3/M	T3/M	T3/S
  Im	Murphy	       S-AL22	5		u  2	0	3	1	0	  50     T2/0
  Im	Chrysanthemum	 V-KU64	60		c  2	0	10	0	0	  650    B1/A  B1/A  T3/M  T3/M  T3/S  T3/S
