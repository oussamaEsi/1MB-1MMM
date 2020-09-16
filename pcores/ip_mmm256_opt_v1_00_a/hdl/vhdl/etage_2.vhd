--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:    11:25:46 06/27/10
-- Design Name:    
-- Module Name:    etage_1 - Behavioral
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
---------------*************************************-------------------
--Ce ciruit permet de calculer Z[j](Ti[j]+(A[i]xB[j])).
--Il reçoit en entrer les mots de l'opérandes A, de l'opérande B, et des résulats intermédiaires Ti[j].
--il est constituer d'un multiplier accumulateur pour calculer A[i]xB[j] et 
-- d'un additonneur   
----------------************************************-----------------
entity etage_2 is
   generic (N    :integer:=32);
   
	port    (clk          :in std_logic;
            op_in        :in std_logic;
	         control_carry:in std_logic;                       --signal d'entrer pour la remise à 0 des retenues 
            A            : IN std_logic_VECTOR(N-1 downto 0); --Bus d'entrer de l'opérande A 
            B            : IN std_logic_VECTOR(N-1 downto 0); --Bus d'entrer de l'opérande B 
	         T            : IN std_logic_VECTOR(N-1 downto 0); --Bus d'entrer des résultats intermédiaire Ti 
            Z            : OUT std_logic_VECTOR(N-1 downto 0);-- bus de donnée de sortie du résulat Z[j] 
				--PP            : OUT std_logic_VECTOR(2*N-1 downto 0);-- bus de donnée de sortie du résulat Z[j] 
				PP            : OUT std_logic_VECTOR(N-1 downto 0);
				Cout         : OUT std_logic_VECTOR(N-1 downto 0));
end etage_2;

architecture Behavioral of etage_2 is

---------**********multiplier accumulateur**********-------------
component multiplieur_accumulateur 
   generic (N    :integer:=32);
   port    (clk          :in std_logic;
            reset_carry     :in std_logic;
				op_in           :in std_logic;
	         X            : IN std_logic_VECTOR(N-1 downto 0);
            Y            : IN std_logic_VECTOR(N-1 downto 0);
            P            : OUT std_logic_VECTOR(N-1 downto 0);
			--	PP            : OUT std_logic_VECTOR(2*N-1 downto 0);
				PP            : OUT std_logic_VECTOR(N-1 downto 0);
				Cout         : OUT std_logic_VECTOR(N-1 downto 0));
end component;
------------------------------------------------------------------
-------********Additionneur à propagation de retenue*******------
component propagate_adder 
   generic (N    :integer:=64);
   port    (A            :in std_logic_vector(N-1 downto 0);
            B            :in std_logic_vector(N-1 downto 0);
            c_in         :in std_logic;
	         S            :out std_logic_vector(N-1 downto 0);
            c_out        :out std_logic);
end component;

component FLIP_FLOP_D 
   port    (reset        :in std_logic;
            clk          :in std_logic;
		      din          :in std_logic;
            dout         :out std_logic);
end component ;


component reg 
  generic  (N    :integer:= 64);
  port     (clk          :in std_logic;
            reset        :in std_logic;
            Din          :in std_logic_vector(N-1 downto 0);
            Dout         :out std_logic_vector(N-1 downto 0));
end component;

signal N_reset           : std_logic;
signal N_P               : std_logic_VECTOR(N-1 downto 0);
signal N1_cy2            :std_logic;
signal N2_cy2            :std_logic;

signal   NZ1              : std_logic_VECTOR(N-1 downto 0);
signal   NZ2              : std_logic_VECTOR(N-1 downto 0);
signal   NZ3              : std_logic_VECTOR(N-1 downto 0);
signal   NZ4              : std_logic_VECTOR(N-1 downto 0);
signal   NZ5              : std_logic_VECTOR(N-1 downto 0);

begin

N_reset <= op_in and control_carry;



UU1:reg 
   generic map(N) 
	port map(clk   => clk,
            reset => op_in,
            Din   => T,
		      Dout  => NZ1);

UU2:reg 
   generic map(N) 
	port map(clk   => clk,
            reset => op_in,
            Din   => NZ1,
		      Dout  => NZ2);		


UU3:reg 
   generic map(N) 
	port map(clk   => clk,
            reset => op_in,
            Din   => NZ2,
		      Dout  => NZ3);

UU4:reg 
   generic map(N) 
	port map(clk   => clk,
            reset => op_in,
            Din   => NZ3,
		      Dout  => NZ4);

UU5:reg 
   generic map(N) 
	port map(clk   => clk,
            reset => op_in,
            Din   => NZ4,
		      Dout  => NZ5);


U1: multiplieur_accumulateur 
         generic map(N)
         port map (clk   => clk,
                   reset_carry => N_reset,
						 op_in => op_in,
                   X     => A,
                   Y     => B,
                   P     => N_P,
						 PP    => PP,
						 Cout  => Cout);

U2: propagate_adder 
         generic map(N)
			port map (A     => NZ5,
                   B     => N_P,
	                c_in  => N1_cy2,
	                S     => Z,
                   c_out => N2_cy2);
U3:FLIP_FLOP_D 
        port map( clk    => clk,
	               reset  => N_reset,
					   din    => N2_cy2,
					   dout   => N1_cy2); 

end Behavioral;
