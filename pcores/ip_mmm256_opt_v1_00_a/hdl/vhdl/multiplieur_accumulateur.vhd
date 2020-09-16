----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:08:48 07/10/2012 
-- Design Name: 
-- Module Name:    multiplieur_accumelateur - Behavioral 
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

-----*****************************-----------------------------------
--- le multiplieur accumulateur permet de caluler une multiplication d'une constante x par une variable Y[j]
--- Il est utliser dans l'etage 1 ou x=A[i], Y=B[j] (A[i] est considéré constant d'une une itération (i).
--- il est utilisé aussi dans l'étage 2 ou x=qi et Y=M[j].
--- il est constité d'un multiplieur (Mul1) et d'un additionneur à propagation de retenue
-----------------------------------------------------------------------


entity multiplieur_accumulateur is
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

end multiplieur_accumulateur;

architecture Behavioral of multiplieur_accumulateur is
component mul1
   port    (clk          :in std_logic;
            sclr        :in std_logic;
	         a            : IN std_logic_VECTOR(N-1 downto 0);
            b            : IN std_logic_VECTOR(N-1 downto 0);
            p            : OUT std_logic_VECTOR(2*N-1 downto 0));
end component;

component propagate_adder 
   generic (N    :integer:=64);
   port    (A            : in std_logic_vector(N-1 downto 0);
            B            : in std_logic_vector(N-1 downto 0);
            c_in         : in std_logic;
	         S            : out std_logic_vector(N-1 downto 0);
            c_out        : out std_logic);
end component;

component reg 
  generic  (N    :integer:= 64);
  port     (clk          : in std_logic;
            reset        : in std_logic;
            Din          : in std_logic_vector(N-1 downto 0);
            Dout         : out std_logic_vector(N-1 downto 0));
end component;


component FLIP_FLOP_D 
  port     (reset        : in std_logic;
            clk          : in std_logic;
		      din          : in std_logic;
            dout         : out std_logic);
end component ;

signal N1                : std_logic_VECTOR(2*N-1 downto 0);
signal N_S1              : std_logic_VECTOR(N-1 downto 0);
signal N_C1              : std_logic_VECTOR(N-1 downto 0);
signal N1_C1             : std_logic_VECTOR(N-1 downto 0);
signal N1_cy1            : std_logic;
signal N2_cy1, N_reset_q : std_logic;

begin
N_reset_q <= not op_in;
U1 : mul1	
     port map (clk=>clk,          
               sclr=>N_reset_q,        
	            a    => X,
		         b    => Y,
					p    => N1);
--PP<=N1;

--N_S1<= N1 (N-1   downto  0); 
PP<=N1 (N-1   downto  0);

N_C1<= N1 (2*N-1 downto  N); 

U2 : reg 
     generic map(N) 
	  port map (clk   => clk,
					reset => op_in,
               Din   => N_C1,
		         Dout  => N1_C1);
											  
Cout<=N1_C1;
U3:propagate_adder 
     generic map(N)
	  port map (--A     => N_S1,
	            A     => N1 (N-1   downto  0),
               B     => N1_C1,
	            c_in  => N1_cy1,
	            S     => P,
               c_out => N2_cy1);
  
	
U4:FLIP_FLOP_D 
     port map (clk   => clk,
	            reset => reset_carry,
					din   => N2_cy1,
					dout  => N1_cy1); 
end Behavioral;