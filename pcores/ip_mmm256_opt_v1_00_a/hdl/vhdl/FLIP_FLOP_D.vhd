library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


 entity FLIP_FLOP_D is

 port(reset:in std_logic;
       clk :in std_logic;
		  din:in std_logic;
       dout:out std_logic);
end FLIP_FLOP_D;

architecture Behavioral of FLIP_FLOP_D is

begin
  process (CLK,reset)
begin
    if reset='0'then
	    dout<= '0';
	 
	 elsif CLK'event and CLK='1' then 
      DOUT <= DIN;
   end if;
end process;



end Behavioral;
