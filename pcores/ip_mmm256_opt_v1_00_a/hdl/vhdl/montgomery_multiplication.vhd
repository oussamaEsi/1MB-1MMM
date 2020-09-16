----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:50:35 04/17/2012 
-- Design Name: 
-- Module Name:    montgomery_multiplication - Behavioral 
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

entity montgomery_multiplication is
    generic ( 
	          m: integer:=5 ;
             N: integer:=32 ;				 
             e    : integer:=32 ); 
    
	 port    (
				run_mmm         : IN STD_LOGIC;
				--run_exp         : IN STD_LOGIC;
	         RESET_IP        : IN STD_LOGIC;
				--Sel_op          : IN STD_LOGIC;
            Load_Cts        : IN STD_LOGIC;
				Load_A_B        : IN STD_LOGIC;
	         Wr_ack          : IN STD_LOGIC;
            read_ack        : IN STD_LOGIC;
	         CLK             : IN STD_LOGIC;
				Din             : in std_logic_VECTOR (N-1 downto 0);
            Exp_result      : out std_logic_vector(N-1 downto 0)
				);
				
end montgomery_multiplication;

architecture Behavioral of montgomery_multiplication is

component control_MMM 
     
	  generic (m: integer:=5 ;
              N: integer:=32;
              e: integer:=32				  ); -- fixe	  
	  port  (
	         RESET_IP        : IN STD_LOGIC;			
				Load_Cts        : IN STD_LOGIC;
				Load_A_B       : IN STD_LOGIC;
	         Wr_ack          : IN STD_LOGIC;
	         read_ack        : IN STD_LOGIC;
	         op_in           : IN STD_LOGIC;
	         CLK             : IN STD_LOGIC;
				--Din             : in std_logic_vector(0 to 31 );
            valid_result1    : OUT std_logic;
				Addr_WM         : out std_logic_vector(m downto 0);
				Addr_W_AB      : OUT std_logic_vector (m downto 0);
				addr_w_i        : out std_logic_vector(m downto 0);
				Addr_R_A        : out std_logic_vector(m downto 0);
				Addr_R_B        : out std_logic_vector(m downto 0);
				Addr_R_N        : out std_logic_vector(m downto 0);
				addr_R_Exp1     : out std_logic_vector(m downto 0);
				En_qi           : out std_logic;
				sel_Z0          : out std_logic;
				Reset_cy12      : out std_logic;
				Reset_cy34      : out std_logic;
				wr_en_fifo      : out std_logic;
				MMM_Status      : out std_logic;
            sel_Reg_Nc      : out std_logic;
				Sel_Mem_M       : out std_logic;
				Sel_Mem_A1      : out std_logic;
				Sel_Mem_B1      : out std_logic
         	);
end component;
--
component aig_addr_din 
 generic ( N    :integer:=32 ;
           m:integer:=5);  
  port   ( reset        : in std_logic;
           clk          : IN std_logic;
			  run_mmm      : in  std_logic;
			  Din          : in  std_logic_vector(N-1 downto 0); -- données en entrées
			  T            : in  std_logic_vector(N-1 downto 0);
			  addr_wm      : in  std_logic_vector(m downto 0); -- bus d'adresse en phase d'écritrure
			  addr_w_ab      : in  std_logic_vector(m downto 0); -- bus d'adresse en phase d'écritrure
			  addr_R_Exp1   : in std_logic_vector(m downto 0);
			  addr_A_R     : in  std_logic_vector(m downto 0); -- bus d'adresse en phase de lecture de la mémoire A 
			  addr_B_R     : in  std_logic_vector(m downto 0); -- bus d'adresse en phase de lecture de la mémoire B
           addr_M_R     : in  std_logic_vector(m downto 0); -- bus d'adresse en phase de lecture de la mémoire B
			  add_w_i      : in  std_logic_vector(m downto 0); -- bus d'adresse en phase d'écritrure
           valid_result1 : in std_logic;
           status       : in  std_logic;                      -- signal pour le démarage de la multiplication de montgomery
			  En_A1        : in  std_logic;
  			  D_A1         : out std_logic_vector(N-1 downto 0); -- bus de donnée d'entrer de la mémoire A
           D_B1         : out std_logic_vector(N-1 downto 0); -- bus de donnée d'entrer de la mémoire B			  
			  D_M          : out std_logic_vector(N-1 downto 0); -- bus de donnée d'entrer de la mémoire B
           addr_M       : out std_logic_vector(m downto 0);
			  addr_A1      : out std_logic_vector(m downto 0); -- bus d'adress de la mémoire A
			  addr_B1      : out std_logic_vector(m downto 0) -- bus d'adress de la mémoire A
		); 
end component;
----
component stockage_unite 
----
    generic (m          : integer:=5 ;
             N          : integer:=32 ); -- fixe
    port    (clk        :in std_logic; 
				 A1         :in std_logic_vector(N-1 downto 0);
	          B1         :in std_logic_vector(N-1 downto 0);
             M_in       :in std_logic_vector(N-1 downto 0);				 
				 wr_en_m    :in std_logic;
				 wr_en_A1   :in std_logic;
				 wr_en_B1   :in std_logic;				 
				 En_M       :in std_logic;
				 En_A1      :in std_logic;
				 En_B1      :in std_logic;
				 addr_A1    :in std_logic_vector(m downto 0);
	          addr_B1    :in std_logic_vector(m downto 0);
				 addr_M     :in std_logic_vector(m downto 0);         
				 Out_A1     :out std_logic_vector(N-1 downto 0);
	          Out_B1     :out std_logic_vector(N-1 downto 0);
				 Out_M     :out std_logic_vector(N-1 downto 0));

end component;
----
component etage_1 
    generic (N          :integer:=64);
    port    (clk        :in std_logic;
             op_in      :in std_logic;
	  control_carry      :in std_logic;
             A          :IN std_logic_VECTOR(N-1 downto 0);
             B          :IN std_logic_VECTOR(N-1 downto 0);
	          T          :IN std_logic_VECTOR(N-1 downto 0);
             Z          :OUT std_logic_VECTOR(N-1 downto 0);
				 PP            : OUT std_logic_VECTOR(N-1 downto 0);
				 Cout       : OUT std_logic_VECTOR(N-1 downto 0));
end component;
--
component reg 
  generic  (N    :integer:= 64);
 port     (clk          : in std_logic;
            reset        : in std_logic;
            Din          : in std_logic_vector(N-1 downto 0);
            Dout         : out std_logic_vector(N-1 downto 0));
end component;
--
component etage_2 
    generic (N          :integer:=64);
    port    (clk        :in std_logic;
             op_in      :in std_logic;
	  control_carry      :in std_logic;
             A          :IN std_logic_VECTOR(N-1 downto 0);
             B          :IN std_logic_VECTOR(N-1 downto 0);
	          T          :IN std_logic_VECTOR(N-1 downto 0);
             Z          :OUT std_logic_VECTOR(N-1 downto 0);
				 PP            : OUT std_logic_VECTOR(N-1 downto 0);
				 Cout       : OUT std_logic_VECTOR(N-1 downto 0));
end component;

signal N1_D                        : std_logic_vector(0 to N-1);
signal N2_D                        : std_logic_vector(0 to N-1); 
signal N_addr_w_i                  : std_logic_vector(m downto 0);  
signal N_addr_A_R                  : std_logic_vector(m downto 0);  
signal N_addr_B_R                  : std_logic_vector(m downto 0);  
signal N_addr_M_R                  : std_logic_vector(m downto 0);
signal N_addr_R_Exp1  : std_logic_vector(m downto 0);      
--signal N_addr_R_Exp1, N_addr_R_Exp2, N_addr_R_Exp  : std_logic_vector(m downto 0);      

signal N_status                    : std_logic;  
signal N_valid_result1  : std_logic;  
--signal N_valid_result1, N_valid_result2, N_valid_result_exp,N_sel_A1A2,Reset_reg_out  : std_logic;  

signal N1_En_M, N1_En_A1, N1_En_B1 : std_logic;
signal N2_En_M, N2_En_A1, N2_En_B1  : std_logic;
signal W_En_A1, W_En_B1  : std_logic;

--signal N1_En_R, N2_En_R          :  std_logic;    
signal N_sel_Reg_Nc                :  std_logic;  
signal Net_DA1 :  std_logic_vector(N-1 downto 0);  
signal Net_DB1 :  std_logic_vector(N-1 downto 0);
--signal Net_DA2 :  std_logic_vector(N-1 downto 0);
--signal Net_DB2 :  std_logic_vector(N-1 downto 0);
signal Net_M   :  std_logic_vector(N-1 downto 0);
signal Net_addr_wm :  std_logic_vector(m downto 0);
signal Net_addr_w_ab :  std_logic_vector(m downto 0);
signal Net_addr_A1 :  std_logic_vector(m downto 0);
--signal Net_addr_A2 :  std_logic_vector(m downto 0);
signal Net_addr_B1 :  std_logic_vector(m downto 0);
--signal Net_addr_B2 :  std_logic_vector(m downto 0);
--signal Net_addr_R :  std_logic_vector(m downto 0);
signal Net_addr_M :   std_logic_vector(m downto 0);
SIGNAL N_control_carry : std_logic;
SIGNAL N_control_carry2: std_logic;
SIGNAL N_ce_qi,N_sel_Z0     : std_logic;
SIGNAL N_wr_en_fifo    : std_logic;
--SIGNAL N_rd_en_fifo    : std_logic;
--signal N1_rst_fifo     : std_logic;
--signal N2_rst_fifo     : std_logic;
SIGNAL N_A1:std_logic_vector(N-1 downto 0);
--SIGNAL N_A2:std_logic_vector(N-1 downto 0);
SIGNAL N_B1:std_logic_vector(N-1 downto 0);
--SIGNAL N_B2:std_logic_vector(N-1 downto 0);
SIGNAL N_M1 :std_logic_vector(N-1 downto 0);
SIGNAL N_M2 :std_logic_vector(N-1 downto 0);
--signal N_R :  std_logic_vector(N-1 downto 0);
signal N_Mc :  std_logic_vector(N-1 downto 0);
SIGNAL N1_TS,N2_TS,N3_TS,N4_TS:std_logic_vector(N-1 downto 0);


SIGNAL N_PP,N1_q,N2_q,N_X,N_Y:std_logic_vector(N-1 downto 0);
SIGNAL N_ZS1:std_logic_vector(N-1 downto 0);
SIGNAL N_ZS2:std_logic_vector(N-1 downto 0);
SIGNAL N_LS:std_logic_vector(N-1 downto 0);
--SIGNAL N_TC:std_logic_vector(N-1 downto 0);
--SIGNAL N_ZC1:std_logic_vector(N-1 downto 0);
--SIGNAL N_ZC2:std_logic_vector(N-1 downto 0);
--SIGNAL N_LC:std_logic_vector(N-1 downto 0);
--SIGNAL BMMM2, N_BMMM2:std_logic_vector(N-1 downto 0);
--SIGNAL AMMM1, N_AMMM1:std_logic_vector(N-1 downto 0);
--SIGNAL BMMM1, N_BMMM1:std_logic_vector(N-1 downto 0);
--Signal N_Ei : std_logic;
--Signal N_Sel_R_A2        :  std_logic;
--SIGNAL select_data_out  : std_logic_vector(1 downto 0);
--SIGNAL N_data_out:std_logic_vector(N-1 downto 0);
--SIGNAL select_BMux1    : std_logic_vector(1 downto 0);

begin


process (Clk,RESET_IP)
begin
   if RESET_IP = '1' then 
	N1_D<=( oTHERS => '0');
	elsif Clk'event and Clk='1' then  
         N1_D <= Din;
   end if;
  
end process;

process (Clk,RESET_IP)
begin
  if RESET_IP = '1' then 
	N2_D<=( oTHERS => '0');
	elsif Clk'event and Clk='1' then  
         N2_D <= N1_D;
   end if;
  
end process;

U1:control_MMM
             generic map(m,N,e)  
                     port map( 
							            RESET_IP     =>  RESET_IP,							
                                 Load_Cts     =>  Load_Cts,
											Load_A_B     =>  Load_A_B,											
							            clk          =>  clk,
											Wr_ack       =>  Wr_ack,
											read_ack     =>  read_ack,
											--Din          =>  Din,
										   op_in        =>  run_mmm,
											valid_result1 => N_valid_result1,
                                 Addr_WM      =>  Net_addr_wm,
											Addr_W_AB    =>  Net_addr_w_ab,										
											addr_w_i     =>  N_addr_w_i,
                                 Addr_R_A     =>  N_addr_A_R,
                                 Addr_R_B     =>  N_addr_B_R,
											Addr_R_N     =>  N_addr_M_R,
                                 addr_R_Exp1  =>  N_addr_R_Exp1,
                                 En_qi        =>  N_ce_qi,
											sel_Z0       =>  N_sel_Z0, 
                                 Reset_cy12   =>  N_control_carry,
				                     Reset_cy34   =>  N_control_carry2,
                                 wr_en_fifo   =>  N_wr_en_fifo, 
				                     MMM_Status   =>  N_status,	
                                 sel_Reg_Nc   => N_sel_Reg_Nc,
											Sel_Mem_M    => N1_En_M,
											Sel_Mem_A1   => N1_En_A1,  
				                     Sel_Mem_B1   => N1_En_B1  																					
        									       );

--
U2: aig_addr_din 
   generic map (N,m)
   port map (reset      =>RESET_IP,    
             clk        => clk,      
             run_mmm    => run_mmm, 				 				 
			    Din        => N2_D,  
			    T          => N4_TS,				 
             addr_R_Exp1 => N_addr_R_Exp1,			 
			    addr_A_R   => N_addr_A_R,
			    addr_B_R   => N_addr_B_R, 
             addr_M_R   => N_addr_M_R,  
			    add_w_i    => N_addr_w_i,  
			    valid_result1=>N_valid_result1,
             status     =>  N_status, 
             En_A1      => N1_En_A1, 			  
  			    D_A1       => Net_DA1, 
             D_B1       => Net_DB1,   
			    D_M        => Net_M,
             addr_wm    => Net_addr_wm,
             addr_w_ab  => Net_addr_w_ab,
			    addr_A1    => Net_addr_A1,    -- bus d'adress de la mémoire A
			    addr_B1    => Net_addr_B1,
			    addr_M     => Net_addr_M			  
);
------
N2_En_M   <= N1_En_M  or run_mmm;
N2_En_A1  <= N1_En_A1 or run_mmm;
N2_En_B1  <= N1_En_B1 or run_mmm;

--N2_En_R <= N1_En_R or run_mmm;

W_En_A1  <=  N1_En_A1 or N_status;
W_En_B1  <=  N1_En_B1 or N_status;

------
U3:stockage_unite 
   generic map (m,N)
	 port map(clk=>clk,
	 	       A1      => Net_DA1,         
	          B1      => Net_DB1,
             M_in    => Net_M, 			 
	          addr_A1 => Net_addr_A1,
				 addr_B1  => Net_addr_B1,
				 addr_M  => Net_addr_M,
				 wr_en_A1 => W_En_A1,
				 wr_en_B1 => W_En_B1,
				 wr_en_m =>  N1_En_M,			 
             En_M   => N2_En_M,
             En_A1  => N2_En_A1,
             En_B1  => N2_En_B1,				 
			    Out_A1  => N_A1,
	          Out_B1  => N_B1,
				 Out_M   => N_M1);

process (run_mmm,Clk)
begin 
 IF run_mmm = '0' THEN 
    N_M2  <= ( oTHERS => '0');  
	  elsif Clk'event and Clk='1' then   
			  N_M2 <= N_M1;        
  end if;
end process;


process (Clk,N_valid_result1)
begin
   if N_valid_result1 ='0' then   
		  Exp_result <=  ( oTHERS => '1');
	   elsif Clk'event and Clk='1' then  
			Exp_result <= N_A1;
   end if;
end process;
------
------------regitre de la constante M4------------------------------
process (Clk,N_sel_Reg_Nc)
begin
	   if Clk'event and Clk='1' then  
		  if n_sel_Reg_Nc ='1' then   
			  N_Mc <= N2_D;
        end if;
		end if;
end process;

-----------------------calcul de S------------------------------------------------------

U4: etage_1
    generic map(N)
    port map(clk=>clk,
			  op_in=>run_mmm,
	        control_carry=>N_control_carry,
           A=>N_A1,			  
           B=>N_B1,
           T=>N4_TS,			  	              
			  PP=>N_PP,
			  Z=>N_ZS1,
			  Cout=>open);
------				 
U5: reg 
  generic map (N)
  port map     (clk=>clk,
					 reset=>run_mmm,
                Din=>N_ZS1,
                Dout=>N_ZS2);
					 

U6: etage_2
    generic map(N)
    port map(clk=>clk,
			  op_in=>run_mmm,
	        control_carry=>N_control_carry2,
           A=>N_X,
           B=>N_Y,
           T=>N_ZS2,			         
			  PP=>N1_q,
			  Z=>N_LS,
			  Cout=>open);

process (Clk,N_wr_en_fifo)
begin
IF N_wr_en_fifo = '0' THEN 
    N1_TS  <= ( oTHERS => '0');  	  
	  elsif Clk'event and Clk='1' then  		   
			  N1_TS <= N_LS;
		end if;
end process;

process (run_mmm, Clk)
begin
IF run_mmm = '0' THEN 
    N2_TS  <= ( oTHERS => '0');  	  
	  elsif Clk'event and Clk='1' then  
			  N2_TS <= N1_TS;
		end if;
end process;

process (run_mmm, Clk)
begin
IF run_mmm = '0' THEN 
    N3_TS  <= ( oTHERS => '0');  	  
	  elsif Clk'event and Clk='1' then  
			  N3_TS <= N2_TS;
		end if;
end process;

process (run_mmm, Clk)
begin
IF run_mmm = '0' THEN 
    N4_TS  <= ( oTHERS => '0');  	  
	  elsif Clk'event and Clk='1' then  
			  N4_TS <= N3_TS;
		end if;
end process;

process (run_mmm,Clk,N_ce_qi)
begin 
 IF run_mmm = '0' THEN 
    N2_q  <= ( oTHERS => '0');  
	  elsif Clk'event and Clk='1' then  
		  if N_ce_qi ='1' then   
			  N2_q <= N1_q;
        end if;
  end if;
end process;

N_X <=  N_ZS2 WHEN N_sel_Z0='1' 
            ELSE N2_q;
					 
N_Y <=  N_Mc WHEN N_sel_Z0='1' 
            ELSE N_M2;					 


end Behavioral;

