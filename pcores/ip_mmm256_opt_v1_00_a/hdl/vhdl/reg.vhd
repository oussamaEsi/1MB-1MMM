library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

--  Uncomment the following lines to use the declarations that are
--  provided for instantiating Xilinx primitive components.
--library UNISIM;
--use UNISIM.VComponents.all;

entity reg is
  generic (N : Integer := 64);
  port(clk:in std_logic;
     reset:in std_logic;
     Din:in std_logic_vector(N-1 downto 0);
     Dout:out std_logic_vector(N-1 downto 0));
end reg;

architecture Behavioral of reg is

begin
 process (clk,reset)
begin    
   if reset ='0' then 
     Dout<= (others => '0');
	elsif clk'event and clk='1' then  
      Dout <= Din;
   end if;
 end process;
end Behavioral;
												  