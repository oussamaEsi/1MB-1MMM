----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:40:55 04/17/2012 
-- Design Name: 
-- Module Name:    aig_addr_din - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity aig_addr_din is
 generic ( N    :integer:=32 ;
           m    :integer:=5);
  
  port   ( reset    : in std_logic;
           clk      : IN std_logic;
			  run_mmm    : in  std_logic;
			  Din      : in  std_logic_vector(N-1 downto 0); -- données en entrées
			  T        : in  std_logic_vector(N-1 downto 0);
			  addr_wm    : in  std_logic_vector(m downto 0); -- bus d'adresse en phase d'écritrure
			  addr_w_ab    : in  std_logic_vector(m downto 0); -- bus d'adresse en phase d'écritrure			  
			  addr_A_R : in  std_logic_vector(m downto 0); -- bus d'adresse en phase de lecture de la mémoire A 
			  addr_B_R : in  std_logic_vector(m downto 0); -- bus d'adresse en phase de lecture de la mémoire B
           addr_M_R : in  std_logic_vector(m downto 0); -- bus d'adresse en phase de lecture de la mémoire B
			  add_w_i  : in  std_logic_vector(m downto 0); -- bus d'adresse en phase d'écritrure
           addr_R_Exp1    : in std_logic_vector(m downto 0);
           status        : in  std_logic;    			  -- signal pour le démarage de la multiplication de montgomery
			  En_A1    : in  std_logic;
			  valid_result1  : in std_logic;
  			  D_A1      : out std_logic_vector(N-1 downto 0); -- bus de donnée d'entrer de la mémoire A
           D_B1      : out std_logic_vector(N-1 downto 0); -- bus de donnée d'entrer de la mémoire B
			  D_M       : out std_logic_vector(N-1 downto 0); -- bus de donnée d'entrer de la mémoire B
           addr_M    : out std_logic_vector(m downto 0);
			  addr_A1   : out std_logic_vector(m downto 0); -- bus d'adress de la mémoire A
           addr_B1    : out std_logic_vector(m downto 0)
			 ); 
end aig_addr_din;

architecture Behavioral of aig_addr_din is

--SIGNAL N_S    : std_logic_vector(N-1 downto 0);----R1
--SIGNAL N_C    : std_logic_vector(N-1 downto 0);----R0
--
SIGNAL select_addr_A1M    : std_logic_vector(3 downto 0);
--SIGNAL select_addr_A1E    : std_logic_vector(2 downto 0);
signal N1_addr_A1         : std_logic_vector(m downto 0);
signal N2_addr_A1         : std_logic_vector(m downto 0);



SIGNAL select_addr_B1E    : std_logic_vector(2 downto 0);
--signal N1_addr_B1         : std_logic_vector(m downto 0);
--signal N2_addr_B1         : std_logic_vector(m downto 0);

begin



D_A1 <= Din WHEN status='0' 
            ELSE T;
 
 

D_B1 <= Din; 

 

D_M   <= Din;         

--------------------------------------------------------------//
   
 
addr_M <=  addr_wm WHEN run_mmm ='0' 
            ELSE addr_M_R;

 



addr_B1 <= addr_w_ab WHEN run_mmm='0' 
            ELSE addr_B_R;
				


select_addr_A1M<=  status & run_mmm & En_A1 & valid_result1;


-----Selection des bus d'adresses vers la mémoire A1------------------------------------------------------------------------

process (select_addr_A1M,addr_w_ab,addr_A_R,add_w_i,addr_R_Exp1)
begin
   case select_addr_A1M is
      when "0010"  => N1_addr_A1 <= addr_w_ab;
      when "0100"  => N1_addr_A1 <= addr_A_R;
      when "1100"  => N1_addr_A1 <= add_w_i;
		when "1101"  => N1_addr_A1 <= add_w_i;
		when "0101"  => N1_addr_A1 <= addr_R_Exp1;
		when "0000"  => N1_addr_A1 <= "0000";
      when others => null;
   end case;
end process;
addr_A1 <=  N1_addr_A1;

			  
end Behavioral;

