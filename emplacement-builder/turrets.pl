

open my $out, '>:raw', 'EMPL.BIN';
print $out pack 'xx';
foreach (<DATA>)
{
	my($name, $tl, $effects, $mcr) = split ' ';

    $name =~ s/_/ /g;
	
	print $out pack("b8", $effects),
	           pack("a28x", uc $name),
			   pack("c", $tl),
			   pack("c", $mcr);
}
close $out;

`cp EMPL.BIN ../src`;
`cp EMPL.BIN ../util`;


#                  TL  effects   mcr/10 
#                      hprsng??
__DATA__
Hybrid_Turret      9   10110000  10            
Single_Laser       8   10000000  3            
Dual_Laser         10  10000000  6            
Missile_Launcher   7   00100000  2            
Dual_Missile       9   00100000  4            
Sandcaster         7   00010000  2            
Particle_Beam      10  01100000  50            
Stealth_Mask       11  00000100  10            
Advanced_Sensors   13  00001000  10           
Black_Globe        16  00000100  10            
