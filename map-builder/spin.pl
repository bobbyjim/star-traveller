use strict;

my %hex2dec = ();
my $i = 0;
foreach (split '', '0123456789ABCDEFGHJKLMNPQRSTUVWXYZ')
{
	$hex2dec{ $_ } = $i;
	++$i;
}

my %starportCode = ( 'X' => 0,  'E' => 1,  'D' => 2,  'C' => 3,   'B' => 4, 'A' => 5 );
my %baseCode     = ( 'N' => 16, 'S' => 32, 'W' => 32, 'NS' => 48, 'NW' => 48 );
my %zoneCode     = ( 'A' => 64, 'R' => 128 );
my %allegCode = (
	Wild => 0,
	Vi   => 1,
	Na   => 2,
	Sw   => 3,
	Pa   => 4,
	Rr   => 5,
	Cs   => 6,
	Du   => 7,
);

my @rec1 = ();
my @rec2 = ();

open IN, "spin.tab";
my $hdr = <IN>;
my @header = split /\t/, $hdr;
foreach (<IN>)
{
	my ($sector, $ss, $hex, $name, $uwp, $bases, $remarks, $zone, $pbg, $alleg, $star, $ix, $ex, $cx, $nobles, $w, $ru) = split /\t/;
	my ($sp, $siz, $atm, $hyd, $pop, $gov, $law, $dash, $tl) = split '', $uwp;
    my ($p, $b, $g) = split '', $pbg;

	# 2 bytes
	my ($col, $row) = $hex =~ /^(..)(..)/;

    # 12 bytes
    $name = uc $name;
   
    # 1 byte
    my $starport = $starportCode{ $sp } + $baseCode{ $bases } + $zoneCode{ $zone };
	#print "starport: [$starportCode{$sp}]\n";

    # 1 byte
	$alleg    = $allegCode{ $alleg };
	$alleg += 64  if $b > 0;
	$alleg += 128 if $g > 0;

	push @rec1, pack('CC', $col, $row)
	          . pack('a11x', $name)
			  . pack('CC', $starport, $alleg);

    my $tradeCodes = 0;
	$remarks =~ s/Ga/Ag/;
	$remarks =~ s/Oc/Wa/;
	foreach my $tc (qw/Ag As De Fl He Hi Ic In Lo Na Ni Po Ri Va Wa/ )
	{
		$tradeCodes <<= 1;
		$tradeCodes++ if $remarks =~ /\b$tc\b/;
	}

	push @rec2, pack('CC', $row, $col),
	            pack('v', $tradeCodes),
				pack('xx'),
	            pack('A9x', $uwp)
				;
}

my $out;

open($out, '>:raw', "SPIN1.BIN");
print $out pack('xx');       # initial 2 commodore bytes
print $out @rec1;
print $out pack( 'x1166' ); # fill the remainder with nulls
close $out;

open($out, '>:raw', "SPIN2.BIN");
print $out pack('xx');       # initial 2 commodore bytes
print $out @rec2;
print $out pack( 'x1166' ); # fill the remainder with nulls
close $out;

`cp *.BIN ../src`;
`cp *.BIN ../util`;
