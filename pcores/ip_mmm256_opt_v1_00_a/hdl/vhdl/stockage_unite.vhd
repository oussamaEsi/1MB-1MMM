--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:    10:24:08 02/28/09
-- Design Name:    
-- Module Name:    stockage_unite - Behavioral
-- Project Name:   
-- Target Device:  
-- Tool versions:  
-- Description:
--
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
--------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity stockage_unite is

    generic (m          : integer:=5 ;-- change with the data size           
             N          : integer:=32 ); -- fixe
    port    (clk        :in std_logic;     
				 A1         :in std_logic_vector(N-1 downto 0);
	          B1         :in std_logic_vector(N-1 downto 0);
			    M_in       :in std_logic_vector(N-1 downto 0);           			 			 	 
				 addr_A1    :in std_logic_vector(m downto 0);
	          addr_B1    :in std_logic_vector(m downto 0);
				 addr_M     :in std_logic_vector(m downto 0);	        	
				 wr_en_m    :in std_logic;
             wr_en_A1   :in std_logic;
				 wr_en_B1   :in std_logic;							 
				 En_M       :in std_logic;
				 En_A1      :in std_logic;
				 En_B1      :in std_logic;							 
	          Out_A1     :out std_logic_vector(N-1 downto 0);
	          Out_B1     :out std_logic_vector(N-1 downto 0);
	          Out_M      :out std_logic_vector(N-1 downto 0));
			
end stockage_unite;

architecture Behavioral of stockage_unite is

component single_port_m
       port (           
			  addra      :IN std_logic_VECTOR(m downto 0);
             clka       :IN std_logic;
             dina       : IN std_logic_VECTOR(N-1 downto 0);
             douta      :OUT std_logic_VECTOR(N-1 downto 0);
              ena        : IN std_logic;
				  wea        : IN std_logic_VECTOR(0 downto 0));
end component;


begin
------ mémoire A1 pour le stockage de X et de R1 pour MMM2
U1: single_port_m 
                  port map(addra => addr_A1,
                           clka  => clk,
                           dina  => A1,
                           douta => Out_A1,
									ena   => En_A1,
                           wea(0)   => wr_en_A1
								  );
------ mémoire B1 pour le stockage de R0 pour MMM2
U2: single_port_m port map(addra => addr_B1,
                           clka  => clk,
                           dina  => B1,
                           douta => Out_B1,
									ena   => En_B1,
                           wea(0)   => wr_en_B1
								   );
									
U5:  single_port_m port map (addra => addr_M,
                             clka  => clk,
									  dina  => M_in,
                             douta => Out_M,
									  ena   => En_M,
									  wea(0)   => wr_en_m
				                 );
									  

				 
							  

end Behavioral;
