
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

Entity  CONTROL_MMM IS
   generic (m: integer:=5 ;
	         N: integer:=3 ;    -- change with the data size        
            e: integer:=32 ); 
   
	PORT    (
            RESET_IP       : IN STD_LOGIC;
				Load_Cts       : IN STD_LOGIC;
				Load_A_B       : IN STD_LOGIC;
				op_in          : IN STD_LOGIC;
				read_ack       : IN STD_LOGIC;
	         Wr_ack         : IN STD_LOGIC;
				CLK            : IN STD_LOGIC;
				--Din            : in std_logic_vector(0 to 31 );
				Addr_WM        : OUT std_logic_vector (m downto 0);
				Addr_W_AB      : OUT std_logic_vector (m downto 0);
			   Addr_R_A       : out std_logic_vector(m downto 0);
				Addr_R_B       : out std_logic_vector(m downto 0);
				Addr_R_N       : out std_logic_vector(m downto 0);				
				addr_w_i       : out std_logic_vector(m downto 0);
				addr_R_Exp1     : out std_logic_vector(m downto 0);
				Sel_Mem_M      : out std_logic;
				Sel_Mem_A1     : out std_logic;
				Sel_Mem_B1     : out std_logic;
				sel_Reg_Nc     : out std_logic;
				En_qi          : out std_logic;
				sel_Z0         : out std_logic;
				Reset_cy12     : out std_logic;
				Reset_cy34     : out std_logic;
				wr_en_fifo     : out std_logic;
				MMM_Status     : out std_logic;			  
				valid_result1   : out std_logic
				);
				
            
   END CONTROL_MMM;


ARCHITECTURE  BEHAVIORAL  OF CONTROL_MMM IS


---------signaux du chargement de p-2-----------------------------------------
--signal N_D            :  std_logic_vector(0 to 31);
--signal N_E1           :  std_logic_vector(1023 downto 0);
--signal N_E2           :  std_logic_vector(1023 downto 0);
--signal size_E         :  std_logic_vector(31 downto 0);
--signal int_size_E1    : integer;
--signal int_size_E2    : integer;
signal counter_1      : integer;
--signal N_load         :  std_logic;
--signal N_shift        :  std_logic;

-------------------------------------------------------------------------------
----------------signaux du chargmentr du modulo et de la constate de montgomery
signal counter_2          : integer;
signal counter_3          : integer;
signal counter_4          : integer;
signal counter_5          : integer;
signal counter_6  : integer;


signal counter_10         : integer;

SIGNAL N_addr_a           : integer ; 
SIGNAL N_addr_b           : integer ; 
SIGNAL N_addr_m           : integer ; 
SIGNAL N_ce_qi            : STD_LOGIC ;  
SIGNAL N3_control_carry   : STD_LOGIC ;  
SIGNAL N1_control_carry2  : STD_LOGIC ; 
SIGNAL N_wr_en_fifo       : STD_LOGIC ;
--SIGNAL N_rd_en_fifo       : STD_LOGIC ;  
--signal N_rst_fifo         : STD_LOGIC ; 
SIGNAL N_status           : STD_LOGIC ;  

signal NT_addr_wm, NT_Addr_w_AB   :  std_logic_vector (m downto 0); -- utilisé pour les selection des signaux de selection des mémoires
--signal NT_addr_w2                 :  std_logic_vector (m downto 0); -- utilisé pour les selection des signaux de selection des mémoires

signal   N_counter_3      :  std_logic_vector (31 downto 0); -- utilisé pour les selection des signaux de selection des mémoires
signal   N_counter_5      :  std_logic_vector (31 downto 0);
signal	N1_addr_w_i		  :  std_logic_vector(m downto 0);

---/////////////////////----------------------------------------------------------------------------------------------

signal   N_Sel_Mem_A1, N_Sel_Mem_B1   :  std_logic;
 

begin

------------------------------------controle_write modulo -----------------
addr_generation_PROCESS:process (clk,counter_2,counter_3,Wr_ack,Load_Cts)

begin  
  if Load_Cts = '1' then
		counter_2 <= 0;
		counter_3 <= 0;		
		Sel_Reg_Nc<='0';
		--N_load_size_E<='0';
		elsif Clk'event and Clk = '1' then
		if Wr_ack='1' then
         counter_2 <= counter_2 + 1; 
			if counter_2=e+1 then 
				   counter_2 <= 1;
               counter_3 <= counter_3 +1 ;					
         end if;
			IF counter_2=0 THEN 
			      counter_3 <= counter_3 +1 ;
         END IF; 						        
			  IF (counter_2 = e+1 and counter_3 = 1 )THEN 
			      Sel_Reg_Nc<='1'; 
					else Sel_Reg_Nc<='0';
         END IF; 											 
		end if;	     		  
  end if;  
end process addr_generation_PROCESS;


NT_Addr_wm    <= conv_std_logic_vector(counter_2,m+1);
N_counter_3  <= conv_std_logic_vector(counter_3,32);           

process (Clk,Load_Cts)
begin
  if Load_Cts = '1' then 
	Addr_WM<=( oTHERS => '0');
	elsif Clk'event and Clk='1' then  
         Addr_WM <= NT_Addr_wm;
   end if;
  
end process;

---- control chip slect memory du modulo -------------------------- 
sel_memory_proc : process(Clk,Load_Cts,N_counter_3 ) 
 begin    
  if Load_Cts = '1' then
        Sel_Mem_M <= '0';	    	  
		  elsif Clk'event and Clk = '1' then 
		  case N_counter_3 is
          when "00000000000000000000000000000001" =>
			       Sel_Mem_M <= '1';	              				 
          when "00000000000000000000000000000010" =>
                Sel_Mem_M <= '0';									 
			when others => null;
        end case;
	end if;	  
end process sel_memory_proc;

    -----------------------------------------
-------------------------Controle et decalage du registre ---------------
---------------------------------------------------


----------------------Chargement des opérandes 
write_AB_PROCESS:process (clk,counter_4,counter_5,Wr_ack,Load_A_B)
      
begin  
 
  if Load_A_B = '1' then
		counter_4 <= 0;
		counter_5 <= 0;
		elsif Clk'event and Clk = '1' then
		if Wr_ack='1' then
         counter_4 <= counter_4 + 1;
			if counter_4=e+1 then 
				   counter_4 <= 1;
               counter_5 <= counter_5 +1 ;					
         end if;
			IF counter_4    =  0 THEN 
			      counter_5 <=  counter_5 +1 ; 			
         END IF;   		
		end if;
	
  end if; 
end process write_AB_PROCESS;
--
NT_Addr_w_AB  <= conv_std_logic_vector(counter_4,m+1);
N_counter_5  <= conv_std_logic_vector(counter_5,32);
--
process (Clk,Load_A_B)
begin
  if Load_A_B = '1' then 
	Addr_W_AB<=( oTHERS => '0');
	elsif Clk'event and Clk='1' then  
         Addr_W_AB <= NT_Addr_w_AB;
   end if;  
end process;
--
--
sel_memory_AB_proc : process(Clk,Load_A_B,N_counter_5 ) 
 begin    
  if Load_A_B = '1' then
        N_Sel_Mem_A1 <= '0';
        N_Sel_Mem_B1 <= '0';		  
		  elsif Clk'event and Clk = '1' then 
		  case N_counter_5 is
          when "00000000000000000000000000000001" =>
			       N_Sel_Mem_A1 <= '1';
                N_Sel_Mem_B1 <= '0';
		        		         					 
          when "00000000000000000000000000000010" =>
                N_Sel_Mem_A1 <= '0';
                N_Sel_Mem_B1 <= '1';
		   	
			 when "00000000000000000000000000000011" =>
                N_Sel_Mem_A1 <= '0';
                N_Sel_Mem_B1 <= '0';		 		 
					 
			when others => null;
        end case;
	end if;	  
end process sel_memory_AB_proc;
--
Sel_Mem_A1<= N_Sel_Mem_A1;
Sel_Mem_B1 <=  N_Sel_Mem_B1;

 

------------------------------------------- chargement de l'exposant.

--------------------stockage des données-------------------------------------
--process (RESET_IP,Clk)
--begin
--   if RESET_IP = '1' then 
--	N_D<=( oTHERS => '0');
--    elsif Clk'event and Clk='1' then  
--			N_D <= Din;
--   end if;
--end process;
----
-------------------------------------------------------------------------------------------------	  
------------*************************************************************************----------
------------procedure de l'éxécution d'une opétation-------------------------- 
------------************************************------------------------------


-------------------------------------------------------------------------

PROCESS(CLK,op_in )
  BEGIN    
	  IF op_in = '0' THEN 
        counter_6<=0;
		  N_addr_a          <= 0;
		  N_addr_b          <= 0;
		  N_addr_m          <= 0;	 
		  N_ce_qi           <= '0';		
        sel_Z0            <= '0';				  
		  N3_control_carry  <= '0';
        N1_control_carry2 <= '1';     
 		  N_wr_en_fifo      <= '0';
        N_status          <= '0';	  
-------- contrle registre A-------------------------------------------------------------------
        ELSIF CLK' EVENT  AND CLK = '1'  THEN 
					  counter_6 <= counter_6+1 ;
					  N_addr_b <= N_addr_b +1 ;
					  N_addr_m <= N_addr_m +1 ;					    
                   if counter_6    =  e+5 then					  
					 		  counter_6   <=  1;	        		   
					     end if; 		
--		--- generationde addr_a------------------------------------------------------------------------ 	   	                          
						  if counter_6    =  e+5 then 						  
					        N_addr_a <=  N_addr_a +1 ;
                    END IF; 					    						 
					     if N_addr_a    =  e+2 then
							  N_status <=  '1' ;
							  else N_status <=  '0' ;
                    END IF; 
						  						  
						  IF counter_6    =  0 THEN 
					        N_addr_a <=  N_addr_a +1 ;
                    END IF;                    						  						  
--		--- generationde addr_b------------------------------------------------------------------------ 
						 if counter_6    =  e+1 then
						     N_addr_b   <=  0; 
					    end if;
						 
                   if counter_6    =  e+2 then					      
							  N_addr_b   <=  0; 
					    end if;
						 
						 if counter_6    =  e+3 then					      
							N_addr_b     <=  0; 
					    end if;
						 
						  if counter_6    =  e+4 then					      
							N_addr_b     <=  0; 
					    end if;
						 
					 
-----------------Remise à 1 de l'adressage de la mémoire B pour entamer une nouvelle itération					    
                   if counter_6    =  e+5 then	
	                  N_addr_b     <=  1;
						 end if;	  
	--- generationde addr_m------------------------------------------------------------------------                    
						  if counter_6    =  0 then
							  N_addr_m   <=  0; 
					     end if;                   
						 if counter_6    =  1 then
							  N_addr_m   <=  0; 
					     end if;

                   if counter_6    =  2 then
							  N_addr_m   <=  0; 
					     end if;						  

                   if counter_6    =  3 then
							  N_addr_m   <=  0; 
					     end if;
						  
					   if counter_6    =  4 then
							  N_addr_m   <=  0; 
					     end if; 
						 
-----control_fifo---------------------------------------------						  
						  if counter_6    =  10 then  --7 ------1
					        N_wr_en_fifo <=  '1'; 
					     end if;
--						  
                    if counter_6    =  7 then  --7 ------1
					        N_wr_en_fifo <=  '0'; 
					     end if;

------- controle partie operative------------------------------------------------------------------------ 	                	               						
						  if counter_6    =  2 then
					        N3_control_carry   <= '1'; 
	                 end if;
------- controle carry_2------------------------------------------------------------------	
						  if counter_6    =  6 then
					         N1_control_carry2 <= '0'; 
						   else 	 N1_control_carry2 <= '1';
						  end if;

------- controle sel_Z0------------------------------------------------------------------	                 
                  if counter_6    =  4 then
					        sel_Z0   <= '1'; 
						  else 	 sel_Z0 <= '0';

	                end if;
                  if counter_6    =  6 then						 
					        N_ce_qi  <= '1'; 
						    else  N_ce_qi <= '0';
					     end if;		

	  END IF;
						  
	END PROCESS; 

Addr_R_N    <= conv_std_logic_vector(N_addr_m,m+1);
Addr_R_A    <= conv_std_logic_vector(N_addr_a,m+1);
Addr_R_B    <= conv_std_logic_vector(N_addr_b,m+1);
MMM_Status  <= N_status;
En_qi       <= N_ce_qi;
Reset_cy12  <= N3_control_carry;
Reset_cy34  <= N1_control_carry2 ;
----
wr_en_fifo  <= N_wr_en_fifo;




--------géneration de de l'adressage addr_wi----------------- 
----
N1_addr_w_i    <= conv_std_logic_vector(N_addr_b,m+1);


process (Clk,op_in)
begin
   if op_in = '0' then 
	addr_w_i<=( oTHERS => '0');
	elsif Clk'event and Clk='1' then  
         addr_w_i <= N1_addr_w_i;
   end if;
end process;
--

timer_PROCESS:process (clk,read_ack,op_in,N_status)
begin  
  if op_in = '0' then  
		counter_10<= 0;
		valid_result1<='0';
		elsif Clk'event and Clk = '1' then
		if read_ack='1' then
			counter_10<=counter_10+1;	         
				 
		end if;
	   if   N_status='1' then  
	     valid_result1<='1'; 
        counter_10<=0;		  
      end if;
		if counter_10=e+2 then	  		
        valid_result1<='0';
	   end if;

		
  end if; 
end process timer_PROCESS;
addr_R_Exp1  <= conv_std_logic_vector(counter_10,m+1);


END BEHAVIORAL;

