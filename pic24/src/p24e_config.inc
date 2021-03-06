;;; FlashForth device configuration for the dsPIC24E

;;; Device memory sizes. Set according to your device.
;;; You can increase the addressable flash range be decreasing the addressable ram.
;;; Below is the setting for max amount of ram for dsPIC24E256GP502
.equ FLASH_SIZE,     0x2a800 ; Flash size in bytes without the high byte
                             ; See program memory size in the device datasheet.
.equ RAM_SIZE,       0x8000  ; Ram size in bytes

.ifndecl IOL1WAY_OFF
.equ IOL1WAY_OFF, 0xffff
.endif

;config __FOSCSEL, IESO_ON & FNOSC_FRC
config __FOSCSEL, IESO_ON & FNOSC_FRCPLL
;config __FOSCSEL, IESO_ON & FNOSC_PRI
;config __FOSC, FCKSM_CSECMD & IOL1WAY_OFF & OSCIOFNC_OFF & POSCMD_HS
;config __FOSC, FCKSM_CSECMD & IOL1WAY_OFF & OSCIOFNC_OFF & POSCMD_NONE
config FWDT, FWDTEN_OFF
;config FDS, GWRP_OFF & GCP_OFF
;config FPOR,
config __FICD, JTAGEN_OFF & ICS_PGD3

.equ PLL_DIV, 30              ; Fcy is 27637 KHz (FRC_PLL)
.equ PLL_FBD, PLL_DIV-2
.equ PLL_POST, 2              ; Do not change
.equ PLL_PRE, 2               ; Do not change
.equ FREQ_FIN, 7372800        ; PLL input frequency.
.equ FREQ_OSC, ( FREQ_FIN*PLL_DIV/PLL_PRE/PLL_POST )  ; PLL output frequency. Used with FRCPLL

;.equ  FREQ_OSC, 7372800        ; Used with FNOSC_FRC POSCMD_NONE
;.equ  FREQ_OSC, 16000000       ; Used with FNOSC_PRI POSCMD_HS/XT and external XTAL

;;; UART1 configuration
.equ BAUDRATE1, 9600 				      ; Serial baudrate UART1. OPERATOR UART -> mandatory
.equ FC1_TYPE, 2                          ; 1 = XON/XOFF, 2=CTS/RTS
.equ AUTOBAUD1, 0                         ; 0 = to use fixed baudrate
                                          ; 1 = Autobaud, First char after reset must be 'U' (0x55)

;;; UART2 configuration
;.equ BAUDRATE2, 38400 				      ; Serial baudrate UART2, comment if not used
.equ FC2_TYPE, 1                          ; 1 = XON/XOFF, 2=CTS/RTS
.equ AUTOBAUD2, 0                         ; 0 = to use fixed baudrate
                                          ; 1 = Autobaud, First char after reset must be 'U' (0x55)

; Map UART1 pins
; See device data sheet for pin mapping explanation
.ifdecl RPINR18
.equ RPINR18VAL, 43          ; U1RXPIN RP43 PB11 pin22 microstick2
.equ U1_RPO_REGISTER, RPOR4  ; RP42         PB10 pin21 microstick2
.equ U1_RPO_VALUE, 0x0001    ; UART1 TX on RP42 pin
.equ U1RTSPORT, LATB
.equ U1RTSTRIS, TRISB
.equ U1RTSPIN, 12
.endif

; Map UART2 pins
; See device data sheet for pin mapping explanation
.ifdecl BAUDRATE2
.ifdecl RPINR19
.equ RPINR19VAL, 0x0001       ; (U2RXPIN)
.equ U2_RPO_REGISTER, RPOR0   ; RP35
.equ U2_RPO_VALUE, 0x0200     ; UART2 TX on RP35 pin
.equ U2RTSPORT, LATB
.equ U2RTSTRIS, TRISB
.equ U2RTSPIN, 3
.endif
.endif

; Default number base
.equ BASE_DEFAULT, 10      ; 16 = hexadecimal, 10 = decimal

; Set to 1 for power save when CPU is idle
.equ IDLE_MODE, 1

; Set to 1 for CPU load measurement
.equ CPU_LOAD, 1

; CPU load indicator led definitions
.equ CPU_LOAD_LED, 1       ; set to 0 to disable
.equ CPU_LOAD_TRIS, TRISA
.equ CPU_LOAD_PORT, PORTA
.equ CPU_LOAD_BIT, 0
.equ CPU_LOAD_LED_POLARITY, 1   ; 0 = low on port turns on led, 1 = high on port turns on led

; Define the startup delay for turnkey words. Milliseconds
.equ TURNKEY_DELAY, 2000  ; milliseconds

; UART buffer sizes
; Valid sizes are 7, 15, 31, 63, 127, 255, 511, 1023, etc.
.equ TX1_BUF_SIZE, 0  ; Use 0 for unbuffered TX.
.equ RX1_BUF_SIZE, 31
.equ RX1_OFF_FILL, 8   ; Fill level for XOFF

.equ TX2_BUF_SIZE, 0  ; Use 0 for unbuffered TX.
.equ RX2_BUF_SIZE, 31
.equ RX2_OFF_FILL, 8   ; Fill level for XOFF

;;; USER AREA sizes for the OPERATOR task
.equ RETURN_STACK_SIZE, 96           ; 48 cells return stack
.equ PARAMETER_STACK_SIZE, 96        ; 48 cells parameter stack
.equ TIB_SIZE, 100                   ; 100 chars tib size
.equ HOLD_SIZE, 10                   ; 10 chars hold area

;;; Storage space for OPERATOR uservariables 2 and upwards
;;; EXAMPLE: 8 user myUserVar  -> define UADDSIZE 8
.equ UADDSIZE, 0

; Set to 1 for extra debug info after an exception reset
.equ DEBUG_INFO, 0

; Set to 1 to see when FF writes to flash and eeprom
; 'F' is printed before each flash write.
; 'E' is printed before each eeprom write
.equ DEBUG_FLASH, 0

; Include the example for calling a C function. C4+,  C4add.c
.equ C_EXAMPLE, 0

; Include the 32-bit float number support
.equ FLOATS, 1

; Set to 1 to allow control-o to reset FlashForth
.equ CTRL_O_WARM_RESET, 1

; Method 1 updates flash and eeprom after each ok prompt.
; Method 2 updates flash and eeprom after no flash or eeprom
; update requests have been made for a time of WRITE_TIMEOUT
.equ WRITE_METHOD, 2
.equ WRITE_TIMEOUT, 300         ; milliseconds

;;; Memory mapping prefixes
.equ SFR_SPACE,      0x1000
.equ PFLASH,         SFR_SPACE+RAM_SIZE
.equ HI_TEMP,        PFLASH+FLASH_SIZE
.if HI_TEMP > 0xffff
.equ FLASH_HI,       (0xffff)
.else
.equ FLASH_HI,       (HI_TEMP-1)
.endif

;;; Flash memory commands. Do not modify.
.equ FLASH_ERASE,    0x4003     ; Memory page erase
.equ FLASH_WRITE,    0x4001     ; Memory row write = double word
.equ FLASH_WRITE_SINGLE, 0x4001 ; Memory double word write
.equ FLASH_WRITE_DOUBLE, 0x4001 ; Memory double word write

;.equ PAIVT,          0x0100
.equ IBUFSIZEL,      0x0800
.equ IBUFSIZEH,      0x0400
.equ IBUFLEN1,       0x0002   ; Inner write loop
.equ IBUFLEN2,       0x0200   ; Outer write loop
.equ IBUFMASK,       0xf800


.equ FCY, (FREQ_OSC/2)
.equ MS_PR_VAL, ((FCY/1000)-1)			      ; Timer value for 1 ms ticks
.equ BAUD_DIV1, (FCY/4/BAUDRATE1)-1		  ; UART1 divisor
.ifdecl BAUDRATE2
.equ BAUD_DIV2, (FCY/4/BAUDRATE2)-1		  ; UART2 divisor
.endif
.equ write_delay, 20                      ; Flash write delay

.if FLASH_SIZE > 0x10000
.equ DPS_BASE, 0
.equ DPS_PAGE, 1
.else
.equ DPS_BASE, CONFIG_DATA
.equ DPS_PAGE, 0
.endif

;;; Different flash write logic for E devices than HJ or FJ devices
.equ PIC2433E, 1

; Amount of interrupt vectors
.equ IVECSIZE, 126
