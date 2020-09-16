library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity propagate_adder is
generic(N:integer:=64);
port(A:in std_logic_vector(N-1 downto 0);
     B:in std_logic_vector(N-1 downto 0);
  c_in:in std_logic;
	  S:out std_logic_vector(N-1 downto 0);
 c_out:out std_logic);

end propagate_adder;

architecture Behavioral of propagate_adder is
component cellule_full_adder 
   port ( c    : in    std_logic; 
          x   : in    std_logic; 
          y   : in    std_logic; 
          c_out : out   std_logic; 
          s : out   std_logic);
end component; 



 signal n1:std_logic_vector(n downto 1);

begin

u1 : for i in 0 to 0 generate
  ui:cellule_full_adder port map( c=>c_in,
                                  x=>A(0),
											 y=>B(0),
											 s=>S(i),
											 c_out=>n1(i+1));
end generate u1;

u2 : for i in 1 to n-1 generate
  ui:cellule_full_adder port map( c=>n1(i),
                                  x=>A(i),
											 y=>B(i),
											 c_out=>n1(i+1),
											 s=>S(i));
end generate u2;
c_out<=n1(n);
--n1(0)<=c_in;

end Behavioral;
