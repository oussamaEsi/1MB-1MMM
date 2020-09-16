----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:51:07 04/22/2012 
-- Design Name: 
-- Module Name:    cellule_full_adder - Behavioral 
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
library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity cellule_full_adder is
port (    c     : in    std_logic; 
          x     : in    std_logic; 
          y     : in    std_logic; 
          c_out : out   std_logic; 
          s     : out   std_logic);
end cellule_full_adder;

architecture Behavioral of cellule_full_adder is

 attribute BOX_TYPE   : string ;
   signal XLXN_5 : std_logic;
   component XOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR2 : component is "BLACK_BOX";
   
   component XORCY
      port ( CI : in    std_logic; 
             LI : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XORCY : component is "BLACK_BOX";
   
   component MUXCY_L
      port ( CI : in    std_logic; 
             DI : in    std_logic; 
             S  : in    std_logic; 
             LO : out   std_logic);
   end component;
   attribute BOX_TYPE of MUXCY_L : component is "BLACK_BOX";
   
begin
   XLXI_2 : XOR2
      port map (I0=>x,
                I1=>y,
                O=>XLXN_5);
   
   XLXI_3 : XORCY
      port map (CI=>c,
                LI=>XLXN_5,
                O=>s);
   
   XLXI_7 : MUXCY_L
      port map (CI=>c,
                DI=>x,
                S=>XLXN_5,
                LO=>c_out);
   
end BEHAVIORAL;





