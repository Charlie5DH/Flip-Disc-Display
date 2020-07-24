
_config_PIC:

;MyProject.c,37 :: 		void config_PIC()
;MyProject.c,39 :: 		ADCON1 = 0x0F;
	MOVLW       15
	MOVWF       ADCON1+0 
;MyProject.c,40 :: 		TRISA = 0x00;      // configurado PORTA como salida
	CLRF        TRISA+0 
;MyProject.c,41 :: 		TRISB = 0x01;      // utilizando la interrupcion del RB0(INT0), resto del puerto como salida
	MOVLW       1
	MOVWF       TRISB+0 
;MyProject.c,42 :: 		TRISC = 0x00;      // configurado PORTC como salida
	CLRF        TRISC+0 
;MyProject.c,43 :: 		TRISD = 0x00;      // configurado PORTD como salida
	CLRF        TRISD+0 
;MyProject.c,44 :: 		TRISE = 0xFF;      // configurado PORTE como entrada
	MOVLW       255
	MOVWF       TRISE+0 
;MyProject.c,46 :: 		PORTA = 0x00;      // inicializando los puertos (borrando los latches)
	CLRF        PORTA+0 
;MyProject.c,47 :: 		PORTB = 0x00;
	CLRF        PORTB+0 
;MyProject.c,48 :: 		PORTC = 0x00;
	CLRF        PORTC+0 
;MyProject.c,49 :: 		PORTD = 0x00;
	CLRF        PORTD+0 
;MyProject.c,50 :: 		}
L_end_config_PIC:
	RETURN      0
; end of _config_PIC

_config_IT:

;MyProject.c,52 :: 		void config_IT()
;MyProject.c,54 :: 		GIE_bit = 1;       //bit activador del permiso global de interrupciones (global interruption enable)
	BSF         GIE_bit+0, BitPos(GIE_bit+0) 
;MyProject.c,55 :: 		IPEN_bit = 0;      // niveles de prioridad no permitidos (interruption priority enable)
	BCF         IPEN_bit+0, BitPos(IPEN_bit+0) 
;MyProject.c,56 :: 		RBPU_bit = 0;      // activador del pull-up interno del puerto B
	BCF         RBPU_bit+0, BitPos(RBPU_bit+0) 
;MyProject.c,57 :: 		INTEDG0_bit = 1;   // selector de flanco de la INT0, frente de subida
	BSF         INTEDG0_bit+0, BitPos(INTEDG0_bit+0) 
;MyProject.c,58 :: 		INT0IE_bit = 1;    // bit de permiso de la interrupcion externa 0 (INT0 input enable)
	BSF         INT0IE_bit+0, BitPos(INT0IE_bit+0) 
;MyProject.c,59 :: 		TMR0IE_bit = 1;    // activado permiso de interrupcion por desbordamiento del TMR0(sirve para enmascarar)
	BSF         TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
;MyProject.c,60 :: 		}
L_end_config_IT:
	RETURN      0
; end of _config_IT

_config_TMR0:

;MyProject.c,61 :: 		void config_TMR0()
;MyProject.c,63 :: 		TMR0ON_bit = 1;    // permite  timer0
	BSF         TMR0ON_bit+0, BitPos(TMR0ON_bit+0) 
;MyProject.c,64 :: 		T08BIT_bit = 0;    // se configura como contador de 16 bits (65536)
	BCF         T08BIT_bit+0, BitPos(T08BIT_bit+0) 
;MyProject.c,65 :: 		T0CS_bit = 0;      // reloj interno del ciclo de instruccion
	BCF         T0CS_bit+0, BitPos(T0CS_bit+0) 
;MyProject.c,66 :: 		PSA_bit = 1;       // no prescaler
	BSF         PSA_bit+0, BitPos(PSA_bit+0) 
;MyProject.c,67 :: 		TMR0L = 0xFF;
	MOVLW       255
	MOVWF       TMR0L+0 
;MyProject.c,68 :: 		TMR0H = 0xFF;
	MOVLW       255
	MOVWF       TMR0H+0 
;MyProject.c,69 :: 		}
L_end_config_TMR0:
	RETURN      0
; end of _config_TMR0

_interrupt:

;MyProject.c,70 :: 		void interrupt(void)
;MyProject.c,72 :: 		USB_Interrupt_Proc();        // mantiene la comunicacion con la PC
	CALL        _USB_Interrupt_Proc+0, 0
;MyProject.c,75 :: 		INT0IF_bit = 0;
	BCF         INT0IF_bit+0, BitPos(INT0IF_bit+0) 
;MyProject.c,77 :: 		}
L_end_interrupt:
L__interrupt71:
	RETFIE      1
; end of _interrupt

_getMap:

;MyProject.c,159 :: 		void getMap()
;MyProject.c,162 :: 		for(i = 0;i < 7;i++)
	CLRF        R2 
	CLRF        R3 
L_getMap1:
	MOVLW       128
	XORWF       R3, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__getMap73
	MOVLW       7
	SUBWF       R2, 0 
L__getMap73:
	BTFSC       STATUS+0, 0 
	GOTO        L_getMap2
;MyProject.c,164 :: 		videoMem[i] = characterMem[initPtrCharMem + i];
	MOVLW       _videoMem+0
	ADDWF       R2, 0 
	MOVWF       FSR1 
	MOVLW       hi_addr(_videoMem+0)
	ADDWFC      R3, 0 
	MOVWF       FSR1H 
	MOVF        R2, 0 
	ADDWF       _initPtrCharMem+0, 0 
	MOVWF       R0 
	MOVF        R3, 0 
	ADDWFC      _initPtrCharMem+1, 0 
	MOVWF       R1 
	MOVLW       _characterMem+0
	ADDWF       R0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(_characterMem+0)
	ADDWFC      R1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       POSTINC1+0 
;MyProject.c,162 :: 		for(i = 0;i < 7;i++)
	INFSNZ      R2, 1 
	INCF        R3, 1 
;MyProject.c,165 :: 		}
	GOTO        L_getMap1
L_getMap2:
;MyProject.c,166 :: 		flagVMemFull = 1;
	BSF         _flagVMemFull+0, BitPos(_flagVMemFull+0) 
;MyProject.c,167 :: 		}
L_end_getMap:
	RETURN      0
; end of _getMap

_get_Array_Size:

;MyProject.c,169 :: 		unsigned char get_Array_Size(unsigned char array[])
;MyProject.c,171 :: 		unsigned char i = 0;
	CLRF        get_Array_Size_i_L0+0 
;MyProject.c,172 :: 		while(i != '\n')
L_get_Array_Size4:
	MOVF        get_Array_Size_i_L0+0, 0 
	XORLW       10
	BTFSC       STATUS+0, 2 
	GOTO        L_get_Array_Size5
;MyProject.c,173 :: 		{i++;}
	INCF        get_Array_Size_i_L0+0, 1 
	GOTO        L_get_Array_Size4
L_get_Array_Size5:
;MyProject.c,174 :: 		return i;
	MOVF        get_Array_Size_i_L0+0, 0 
	MOVWF       R0 
;MyProject.c,175 :: 		}
L_end_get_Array_Size:
	RETURN      0
; end of _get_Array_Size

_visualizar:

;MyProject.c,177 :: 		void visualizar()
;MyProject.c,179 :: 		unsigned char i = 0x00;
	CLRF        visualizar_i_L0+0 
	MOVLW       1
	MOVWF       visualizar_j_L0+0 
	CLRF        visualizar_signal_L0+0 
;MyProject.c,183 :: 		flagVMemFull = 0;
	BCF         _flagVMemFull+0, BitPos(_flagVMemFull+0) 
;MyProject.c,184 :: 		if(flagScreenEn == 1)
	BTFSS       _flagScreenEn+0, BitPos(_flagScreenEn+0) 
	GOTO        L_visualizar6
;MyProject.c,186 :: 		flagScreenEn = 0;
	BCF         _flagScreenEn+0, BitPos(_flagScreenEn+0) 
;MyProject.c,187 :: 		pixel = (videoMem[ptrVideoMem] >> fila) & 0x01;      // obtener el pixel a girar(getbit)
	MOVLW       _videoMem+0
	MOVWF       FSR0 
	MOVLW       hi_addr(_videoMem+0)
	MOVWF       FSR0H 
	MOVF        _ptrVideoMem+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       R2 
	MOVF        _fila+0, 0 
	MOVWF       R1 
	MOVF        R2, 0 
	MOVWF       R0 
	MOVF        R1, 0 
L__visualizar76:
	BZ          L__visualizar77
	RRCF        R0, 1 
	BCF         R0, 7 
	ADDLW       255
	GOTO        L__visualizar76
L__visualizar77:
	MOVLW       1
	ANDWF       R0, 1 
	BTFSC       R0, 0 
	GOTO        L__visualizar78
	BCF         _pixel+0, BitPos(_pixel+0) 
	GOTO        L__visualizar79
L__visualizar78:
	BSF         _pixel+0, BitPos(_pixel+0) 
L__visualizar79:
;MyProject.c,189 :: 		while(cursor != i && cursor < 18){ i++; }
L_visualizar7:
	MOVF        _cursor+0, 0 
	XORWF       visualizar_i_L0+0, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L_visualizar8
	MOVLW       18
	SUBWF       _cursor+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_visualizar8
L__visualizar62:
	INCF        visualizar_i_L0+0, 1 
	GOTO        L_visualizar7
L_visualizar8:
;MyProject.c,190 :: 		while(ptrVideoMem != j && ptrVideoMem < 8){ j++; }
L_visualizar11:
	MOVF        _ptrVideoMem+0, 0 
	XORWF       visualizar_j_L0+0, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L_visualizar12
	MOVLW       8
	SUBWF       _ptrVideoMem+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_visualizar12
L__visualizar61:
	INCF        visualizar_j_L0+0, 1 
	GOTO        L_visualizar11
L_visualizar12:
;MyProject.c,191 :: 		signal = (j << 1);                                    // ubicados A0,A1,A2 (bits 1,2 y 3)
	MOVF        visualizar_j_L0+0, 0 
	MOVWF       R2 
	RLCF        R2, 1 
	BCF         R2, 0 
	MOVF        R2, 0 
	MOVWF       visualizar_signal_L0+0 
;MyProject.c,192 :: 		signal = ((i << 4) & 0x10) | signal;                // hallando el valor de B0 y ubicandolo en el 5to bit de la palabra
	MOVF        visualizar_i_L0+0, 0 
	MOVWF       R0 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R0, 1 
	BCF         R0, 0 
	MOVLW       16
	ANDWF       R0, 1 
	MOVF        R0, 0 
	IORWF       R2, 1 
	MOVF        R2, 0 
	MOVWF       visualizar_signal_L0+0 
;MyProject.c,193 :: 		signal = ((array_B1_values[i] << 5) | signal);      // hallando el valor de B1 y ubicandolo en su posicicon correespondiente
	MOVLW       _array_B1_values+0
	MOVWF       FSR0 
	MOVLW       hi_addr(_array_B1_values+0)
	MOVWF       FSR0H 
	MOVF        visualizar_i_L0+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       R1 
	MOVLW       5
	MOVWF       R0 
	MOVF        R1, 0 
	MOVWF       visualizar_signal_L0+0 
	MOVF        R0, 0 
L__visualizar80:
	BZ          L__visualizar81
	RLCF        visualizar_signal_L0+0, 1 
	BCF         visualizar_signal_L0+0, 0 
	ADDLW       255
	GOTO        L__visualizar80
L__visualizar81:
	MOVF        R2, 0 
	IORWF       visualizar_signal_L0+0, 1 
;MyProject.c,195 :: 		if(pixel == 1)                                       // si es encendido el pixel
	BTFSS       _pixel+0, BitPos(_pixel+0) 
	GOTO        L_visualizar15
;MyProject.c,197 :: 		EN_ON_OFF = 0;                                      // habilita los decodificadores para encender
	BCF         RD3_bit+0, BitPos(RD3_bit+0) 
;MyProject.c,198 :: 		signal = signal & 0xBF;                             // DATO en 0 (bit 6 de signal)
	MOVLW       191
	ANDWF       visualizar_signal_L0+0, 1 
;MyProject.c,199 :: 		}
	GOTO        L_visualizar16
L_visualizar15:
;MyProject.c,202 :: 		EN_ON_OFF = 1;                                      //habilita los decoder para apagar
	BSF         RD3_bit+0, BitPos(RD3_bit+0) 
;MyProject.c,203 :: 		signal = signal | 0x40;                             // DATO en 1 (bit 6 de signal)
	BSF         visualizar_signal_L0+0, 6 
;MyProject.c,204 :: 		}
L_visualizar16:
;MyProject.c,205 :: 		PORTB = signal;                                     // escribe en PB <- A0,A1,A2,B0,B1,DATO
	MOVF        visualizar_signal_L0+0, 0 
	MOVWF       PORTB+0 
;MyProject.c,207 :: 		if(fWrap == 1) { EN_UP_DOWN = 0x00; }
	BTFSS       _fWrap+0, BitPos(_fWrap+0) 
	GOTO        L_visualizar17
	BCF         RD4_bit+0, BitPos(RD4_bit+0) 
	GOTO        L_visualizar18
L_visualizar17:
;MyProject.c,208 :: 		else { EN_UP_DOWN = 0x01; }
	BSF         RD4_bit+0, BitPos(RD4_bit+0) 
L_visualizar18:
;MyProject.c,210 :: 		if(ptrCharMem == tamMsg) { flagScreenEn = 0x00; }
	MOVF        _ptrCharMem+0, 0 
	XORWF       _tamMsg+0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_visualizar19
	BCF         _flagScreenEn+0, BitPos(_flagScreenEn+0) 
	GOTO        L_visualizar20
L_visualizar19:
;MyProject.c,211 :: 		else { flagScreenEn = 0x01; }
	BSF         _flagScreenEn+0, BitPos(_flagScreenEn+0) 
L_visualizar20:
;MyProject.c,213 :: 		PORTD = (PORTD & 0x18) | (fila & 0x07);              // leer del mismo puerto para no afectar los valores de los EN (mandar fila)
	MOVLW       24
	ANDWF       PORTD+0, 0 
	MOVWF       R1 
	MOVLW       7
	ANDWF       _fila+0, 0 
	MOVWF       R0 
	MOVF        R0, 0 
	IORWF       R1, 0 
	MOVWF       PORTD+0 
;MyProject.c,216 :: 		PORTA = 0x00;                                        // enable de los decodificadores en nivel bajo para dar el pulso
	CLRF        PORTA+0 
;MyProject.c,217 :: 		Delay_ms(1);
	MOVLW       7
	MOVWF       R12, 0
	MOVLW       125
	MOVWF       R13, 0
L_visualizar21:
	DECFSZ      R13, 1, 1
	BRA         L_visualizar21
	DECFSZ      R12, 1, 1
	BRA         L_visualizar21
;MyProject.c,218 :: 		PORTA = array_EN_values[cursor];
	MOVLW       _array_EN_values+0
	MOVWF       FSR0 
	MOVLW       hi_addr(_array_EN_values+0)
	MOVWF       FSR0H 
	MOVF        _cursor+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       PORTA+0 
;MyProject.c,219 :: 		Delay_ms(1);
	MOVLW       7
	MOVWF       R12, 0
	MOVLW       125
	MOVWF       R13, 0
L_visualizar22:
	DECFSZ      R13, 1, 1
	BRA         L_visualizar22
	DECFSZ      R12, 1, 1
	BRA         L_visualizar22
;MyProject.c,220 :: 		PORTA = 0x00;
	CLRF        PORTA+0 
;MyProject.c,222 :: 		fila = fila +1;                                      // acceder al siguiente bit
	INCF        _fila+0, 1 
;MyProject.c,223 :: 		if(fila == 8)                                        //terminando la columna
	MOVF        _fila+0, 0 
	XORLW       8
	BTFSS       STATUS+0, 2 
	GOTO        L_visualizar23
;MyProject.c,225 :: 		ptrVideoMem = ptrVideoMem + 1;
	INCF        _ptrVideoMem+0, 1 
;MyProject.c,226 :: 		fila = 0;
	CLRF        _fila+0 
;MyProject.c,227 :: 		if(ptrVideoMem == 7)                                // termino el caracter
	MOVF        _ptrVideoMem+0, 0 
	XORLW       7
	BTFSS       STATUS+0, 2 
	GOTO        L_visualizar24
;MyProject.c,229 :: 		ptrVideoMem = 0;
	CLRF        _ptrVideoMem+0 
;MyProject.c,230 :: 		flagVMemFull = 0;                                  //desechar memoria de video
	BCF         _flagVMemFull+0, BitPos(_flagVMemFull+0) 
;MyProject.c,231 :: 		initPtrCharMem = initPtrCharMem + 7;
	MOVLW       7
	ADDWF       _initPtrCharMem+0, 1 
	MOVLW       0
	ADDWFC      _initPtrCharMem+1, 1 
;MyProject.c,232 :: 		cursor = cursor + 1;
	INCF        _cursor+0, 1 
;MyProject.c,233 :: 		aux0 = aux0 + 1;
	INFSNZ      _aux0+0, 1 
	INCF        _aux0+1, 1 
;MyProject.c,234 :: 		flagScreenEn = 0x01;
	BSF         _flagScreenEn+0, BitPos(_flagScreenEn+0) 
;MyProject.c,235 :: 		if(cursor == 17)                                   // finalizado primer renglon
	MOVF        _cursor+0, 0 
	XORLW       17
	BTFSS       STATUS+0, 2 
	GOTO        L_visualizar25
;MyProject.c,237 :: 		fWrap = !fWrap;
	BTG         _fWrap+0, BitPos(_fWrap+0) 
;MyProject.c,238 :: 		cursor = 2;
	MOVLW       2
	MOVWF       _cursor+0 
;MyProject.c,239 :: 		}
L_visualizar25:
;MyProject.c,240 :: 		}
L_visualizar24:
;MyProject.c,241 :: 		}
L_visualizar23:
;MyProject.c,242 :: 		}
L_visualizar6:
;MyProject.c,243 :: 		}
L_end_visualizar:
	RETURN      0
; end of _visualizar

_visualizar_invertido:

;MyProject.c,245 :: 		void visualizar_invertido()
;MyProject.c,247 :: 		unsigned char i = 0x00;
	CLRF        visualizar_invertido_i_L0+0 
	MOVLW       1
	MOVWF       visualizar_invertido_j_L0+0 
	CLRF        visualizar_invertido_signal_L0+0 
;MyProject.c,251 :: 		flagVMemFull = 0;
	BCF         _flagVMemFull+0, BitPos(_flagVMemFull+0) 
;MyProject.c,252 :: 		if(flagScreenEn == 1)
	BTFSS       _flagScreenEn+0, BitPos(_flagScreenEn+0) 
	GOTO        L_visualizar_invertido26
;MyProject.c,254 :: 		flagScreenEn = 0;
	BCF         _flagScreenEn+0, BitPos(_flagScreenEn+0) 
;MyProject.c,255 :: 		pixel = (videoMem[ptrVideoMem] >> fila) & 0x01;      // obtener el pixel a girar(getbit)
	MOVLW       _videoMem+0
	MOVWF       FSR0 
	MOVLW       hi_addr(_videoMem+0)
	MOVWF       FSR0H 
	MOVF        _ptrVideoMem+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       R2 
	MOVF        _fila+0, 0 
	MOVWF       R1 
	MOVF        R2, 0 
	MOVWF       R0 
	MOVF        R1, 0 
L__visualizar_invertido83:
	BZ          L__visualizar_invertido84
	RRCF        R0, 1 
	BCF         R0, 7 
	ADDLW       255
	GOTO        L__visualizar_invertido83
L__visualizar_invertido84:
	MOVLW       1
	ANDWF       R0, 1 
	BTFSC       R0, 0 
	GOTO        L__visualizar_invertido85
	BCF         _pixel+0, BitPos(_pixel+0) 
	GOTO        L__visualizar_invertido86
L__visualizar_invertido85:
	BSF         _pixel+0, BitPos(_pixel+0) 
L__visualizar_invertido86:
;MyProject.c,257 :: 		while(cursor != i && cursor < 18){ i++; }
L_visualizar_invertido27:
	MOVF        _cursor+0, 0 
	XORWF       visualizar_invertido_i_L0+0, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L_visualizar_invertido28
	MOVLW       18
	SUBWF       _cursor+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_visualizar_invertido28
L__visualizar_invertido64:
	INCF        visualizar_invertido_i_L0+0, 1 
	GOTO        L_visualizar_invertido27
L_visualizar_invertido28:
;MyProject.c,258 :: 		while(ptrVideoMem != j && ptrVideoMem < 8){ j++; }
L_visualizar_invertido31:
	MOVF        _ptrVideoMem+0, 0 
	XORWF       visualizar_invertido_j_L0+0, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L_visualizar_invertido32
	MOVLW       8
	SUBWF       _ptrVideoMem+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_visualizar_invertido32
L__visualizar_invertido63:
	INCF        visualizar_invertido_j_L0+0, 1 
	GOTO        L_visualizar_invertido31
L_visualizar_invertido32:
;MyProject.c,259 :: 		signal = (j << 1);                                    // ubicados A0,A1,A2 (bits 1,2 y 3)
	MOVF        visualizar_invertido_j_L0+0, 0 
	MOVWF       R2 
	RLCF        R2, 1 
	BCF         R2, 0 
	MOVF        R2, 0 
	MOVWF       visualizar_invertido_signal_L0+0 
;MyProject.c,260 :: 		signal = ((i << 4) & 0x10) | signal;                // hallando el valor de B0 y ubicandolo en el 5to bit de la palabra
	MOVF        visualizar_invertido_i_L0+0, 0 
	MOVWF       R0 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R0, 1 
	BCF         R0, 0 
	MOVLW       16
	ANDWF       R0, 1 
	MOVF        R0, 0 
	IORWF       R2, 1 
	MOVF        R2, 0 
	MOVWF       visualizar_invertido_signal_L0+0 
;MyProject.c,261 :: 		signal = ((array_B1_values[i] << 5) | signal);      // hallando el valor de B1 y ubicandolo en su posicicon correespondiente
	MOVLW       _array_B1_values+0
	MOVWF       FSR0 
	MOVLW       hi_addr(_array_B1_values+0)
	MOVWF       FSR0H 
	MOVF        visualizar_invertido_i_L0+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       R1 
	MOVLW       5
	MOVWF       R0 
	MOVF        R1, 0 
	MOVWF       visualizar_invertido_signal_L0+0 
	MOVF        R0, 0 
L__visualizar_invertido87:
	BZ          L__visualizar_invertido88
	RLCF        visualizar_invertido_signal_L0+0, 1 
	BCF         visualizar_invertido_signal_L0+0, 0 
	ADDLW       255
	GOTO        L__visualizar_invertido87
L__visualizar_invertido88:
	MOVF        R2, 0 
	IORWF       visualizar_invertido_signal_L0+0, 1 
;MyProject.c,263 :: 		if(pixel == 0)                                       // si es encendido el pixel
	BTFSC       _pixel+0, BitPos(_pixel+0) 
	GOTO        L_visualizar_invertido35
;MyProject.c,265 :: 		EN_ON_OFF = 0;                                      // habilita los decodificadores para encender
	BCF         RD3_bit+0, BitPos(RD3_bit+0) 
;MyProject.c,266 :: 		signal = signal & 0xBF;                             // DATO en 0 (bit 6 de signal)
	MOVLW       191
	ANDWF       visualizar_invertido_signal_L0+0, 1 
;MyProject.c,267 :: 		}
	GOTO        L_visualizar_invertido36
L_visualizar_invertido35:
;MyProject.c,270 :: 		EN_ON_OFF = 1;                                      //habilita los decoder para apagar
	BSF         RD3_bit+0, BitPos(RD3_bit+0) 
;MyProject.c,271 :: 		signal = signal | 0x40;                             // DATO en 1 (bit 6 de signal)
	BSF         visualizar_invertido_signal_L0+0, 6 
;MyProject.c,272 :: 		}
L_visualizar_invertido36:
;MyProject.c,273 :: 		PORTB = signal;                                     // escribe en PB <- A0,A1,A2,B0,B1,DATO
	MOVF        visualizar_invertido_signal_L0+0, 0 
	MOVWF       PORTB+0 
;MyProject.c,275 :: 		if(fWrap == 1) { EN_UP_DOWN = 0x00; }
	BTFSS       _fWrap+0, BitPos(_fWrap+0) 
	GOTO        L_visualizar_invertido37
	BCF         RD4_bit+0, BitPos(RD4_bit+0) 
	GOTO        L_visualizar_invertido38
L_visualizar_invertido37:
;MyProject.c,276 :: 		else { EN_UP_DOWN = 0x01; }
	BSF         RD4_bit+0, BitPos(RD4_bit+0) 
L_visualizar_invertido38:
;MyProject.c,278 :: 		PORTD = (PORTD & 0x18) | (fila & 0x07);              // leer del mismo puerto para no afectar los valores de los EN (mandar fila)     Mascara
	MOVLW       24
	ANDWF       PORTD+0, 0 
	MOVWF       R1 
	MOVLW       7
	ANDWF       _fila+0, 0 
	MOVWF       R0 
	MOVF        R0, 0 
	IORWF       R1, 0 
	MOVWF       PORTD+0 
;MyProject.c,280 :: 		if(ptrCharMem == tamMsg) { flagScreenEn = 0x00; }
	MOVF        _ptrCharMem+0, 0 
	XORWF       _tamMsg+0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_visualizar_invertido39
	BCF         _flagScreenEn+0, BitPos(_flagScreenEn+0) 
	GOTO        L_visualizar_invertido40
L_visualizar_invertido39:
;MyProject.c,281 :: 		else { flagScreenEn = 0x01; }
	BSF         _flagScreenEn+0, BitPos(_flagScreenEn+0) 
L_visualizar_invertido40:
;MyProject.c,284 :: 		PORTA = 0x00;                                        // enable de los decodificadores en nivel bajo para dar el pulso
	CLRF        PORTA+0 
;MyProject.c,285 :: 		Delay_ms(1);
	MOVLW       7
	MOVWF       R12, 0
	MOVLW       125
	MOVWF       R13, 0
L_visualizar_invertido41:
	DECFSZ      R13, 1, 1
	BRA         L_visualizar_invertido41
	DECFSZ      R12, 1, 1
	BRA         L_visualizar_invertido41
;MyProject.c,286 :: 		PORTA = array_EN_values[cursor];
	MOVLW       _array_EN_values+0
	MOVWF       FSR0 
	MOVLW       hi_addr(_array_EN_values+0)
	MOVWF       FSR0H 
	MOVF        _cursor+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       PORTA+0 
;MyProject.c,287 :: 		Delay_ms(1);
	MOVLW       7
	MOVWF       R12, 0
	MOVLW       125
	MOVWF       R13, 0
L_visualizar_invertido42:
	DECFSZ      R13, 1, 1
	BRA         L_visualizar_invertido42
	DECFSZ      R12, 1, 1
	BRA         L_visualizar_invertido42
;MyProject.c,288 :: 		PORTA = 0x00;
	CLRF        PORTA+0 
;MyProject.c,290 :: 		fila = fila +1;                                      // acceder al siguiente bit
	INCF        _fila+0, 1 
;MyProject.c,291 :: 		if(fila == 8)                                        //terminando la columna
	MOVF        _fila+0, 0 
	XORLW       8
	BTFSS       STATUS+0, 2 
	GOTO        L_visualizar_invertido43
;MyProject.c,293 :: 		ptrVideoMem = ptrVideoMem + 1;
	INCF        _ptrVideoMem+0, 1 
;MyProject.c,294 :: 		fila = 0;
	CLRF        _fila+0 
;MyProject.c,295 :: 		if(ptrVideoMem == 7)                                // termino el caracter
	MOVF        _ptrVideoMem+0, 0 
	XORLW       7
	BTFSS       STATUS+0, 2 
	GOTO        L_visualizar_invertido44
;MyProject.c,297 :: 		ptrVideoMem = 0;
	CLRF        _ptrVideoMem+0 
;MyProject.c,298 :: 		flagVMemFull = 0;                                  //desechar memoria de video
	BCF         _flagVMemFull+0, BitPos(_flagVMemFull+0) 
;MyProject.c,299 :: 		initPtrCharMem = initPtrCharMem + 7;
	MOVLW       7
	ADDWF       _initPtrCharMem+0, 1 
	MOVLW       0
	ADDWFC      _initPtrCharMem+1, 1 
;MyProject.c,300 :: 		cursor = cursor + 1;
	INCF        _cursor+0, 1 
;MyProject.c,301 :: 		aux0 = aux0 + 1;
	INFSNZ      _aux0+0, 1 
	INCF        _aux0+1, 1 
;MyProject.c,302 :: 		flagScreenEn = 0x01;
	BSF         _flagScreenEn+0, BitPos(_flagScreenEn+0) 
;MyProject.c,303 :: 		if(cursor == 18)                                   // finalizado primer renglon
	MOVF        _cursor+0, 0 
	XORLW       18
	BTFSS       STATUS+0, 2 
	GOTO        L_visualizar_invertido45
;MyProject.c,305 :: 		fWrap = !fWrap;
	BTG         _fWrap+0, BitPos(_fWrap+0) 
;MyProject.c,306 :: 		cursor = 2;
	MOVLW       2
	MOVWF       _cursor+0 
;MyProject.c,307 :: 		}
L_visualizar_invertido45:
;MyProject.c,308 :: 		}
L_visualizar_invertido44:
;MyProject.c,309 :: 		}
L_visualizar_invertido43:
;MyProject.c,310 :: 		}
L_visualizar_invertido26:
;MyProject.c,311 :: 		}
L_end_visualizar_invertido:
	RETURN      0
; end of _visualizar_invertido

_main:

;MyProject.c,313 :: 		void main() {
;MyProject.c,315 :: 		flagVMemFull = 0;
	BCF         _flagVMemFull+0, BitPos(_flagVMemFull+0) 
;MyProject.c,316 :: 		flagScreenEn = 1;
	BSF         _flagScreenEn+0, BitPos(_flagScreenEn+0) 
;MyProject.c,317 :: 		pixel = 0;
	BCF         _pixel+0, BitPos(_pixel+0) 
;MyProject.c,318 :: 		fWrap = 0;
	BCF         _fWrap+0, BitPos(_fWrap+0) 
;MyProject.c,320 :: 		config_PIC();
	CALL        _config_PIC+0, 0
;MyProject.c,321 :: 		config_IT();
	CALL        _config_IT+0, 0
;MyProject.c,322 :: 		HID_Enable(&readUSB,&writeUSB);
	MOVLW       _readUSB+0
	MOVWF       FARG_HID_Enable_readbuff+0 
	MOVLW       hi_addr(_readUSB+0)
	MOVWF       FARG_HID_Enable_readbuff+1 
	MOVLW       _writeUSB+0
	MOVWF       FARG_HID_Enable_writebuff+0 
	MOVLW       hi_addr(_writeUSB+0)
	MOVWF       FARG_HID_Enable_writebuff+1 
	CALL        _HID_Enable+0, 0
;MyProject.c,324 :: 		while(1){
L_main46:
;MyProject.c,325 :: 		L_USB = 0;
	BCF         RC6_bit+0, BitPos(RC6_bit+0) 
;MyProject.c,326 :: 		sizeUSB = HID_Read();                 //Devuelve el numero de bytes recibidos
	CALL        _HID_Read+0, 0
	MOVF        R0, 0 
	MOVWF       _sizeUSB+0 
;MyProject.c,327 :: 		if(sizeUSB)                           // si se han recibido datos de la PC
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main48
;MyProject.c,329 :: 		L_USB = 1;
	BSF         RC6_bit+0, BitPos(RC6_bit+0) 
;MyProject.c,330 :: 		buffer_USB = readUSB[0];             // recibido caracter por USB
	MOVF        1280, 0 
	MOVWF       _buffer_USB+0 
;MyProject.c,331 :: 		invertido = readUSB[1];              // invertir colores
	MOVF        1281, 0 
	MOVWF       _invertido+0 
;MyProject.c,332 :: 		mensaje_flag = readUSB[2];
	MOVF        1282, 0 
	MOVWF       _mensaje_flag+0 
;MyProject.c,333 :: 		erase_flag = readUSB[3];
	MOVF        1283, 0 
	MOVWF       _erase_flag+0 
;MyProject.c,334 :: 		contador = contador +1;
	INCF        _contador+0, 1 
;MyProject.c,336 :: 		if(aux0 < contador)
	MOVLW       0
	SUBWF       _aux0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main90
	MOVF        _contador+0, 0 
	SUBWF       _aux0+0, 0 
L__main90:
	BTFSC       STATUS+0, 0 
	GOTO        L_main49
;MyProject.c,338 :: 		if (mensaje_flag == 'a'){ ptrCharMem = mensaje1[aux0] - 0x30; tamMsg = get_Array_Size(mensaje1); }
	MOVF        _mensaje_flag+0, 0 
	XORLW       97
	BTFSS       STATUS+0, 2 
	GOTO        L_main50
	MOVLW       _mensaje1+0
	ADDWF       _aux0+0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(_mensaje1+0)
	ADDWFC      _aux0+1, 0 
	MOVWF       FSR0H 
	MOVLW       48
	SUBWF       POSTINC0+0, 0 
	MOVWF       _ptrCharMem+0 
	MOVLW       _mensaje1+0
	MOVWF       FARG_get_Array_Size_array+0 
	MOVLW       hi_addr(_mensaje1+0)
	MOVWF       FARG_get_Array_Size_array+1 
	CALL        _get_Array_Size+0, 0
	MOVF        R0, 0 
	MOVWF       _tamMsg+0 
L_main50:
;MyProject.c,339 :: 		if (mensaje_flag == 'b'){ ptrCharMem = mensaje2[aux0] - 0x30; tamMsg = get_Array_Size(mensaje2); }
	MOVF        _mensaje_flag+0, 0 
	XORLW       98
	BTFSS       STATUS+0, 2 
	GOTO        L_main51
	MOVLW       _mensaje2+0
	ADDWF       _aux0+0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(_mensaje2+0)
	ADDWFC      _aux0+1, 0 
	MOVWF       FSR0H 
	MOVLW       48
	SUBWF       POSTINC0+0, 0 
	MOVWF       _ptrCharMem+0 
	MOVLW       _mensaje2+0
	MOVWF       FARG_get_Array_Size_array+0 
	MOVLW       hi_addr(_mensaje2+0)
	MOVWF       FARG_get_Array_Size_array+1 
	CALL        _get_Array_Size+0, 0
	MOVF        R0, 0 
	MOVWF       _tamMsg+0 
L_main51:
;MyProject.c,340 :: 		if (mensaje_flag == 'c'){ ptrCharMem = mensaje3[aux0] - 0x30; tamMsg = get_Array_Size(mensaje3); }
	MOVF        _mensaje_flag+0, 0 
	XORLW       99
	BTFSS       STATUS+0, 2 
	GOTO        L_main52
	MOVLW       _mensaje3+0
	ADDWF       _aux0+0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(_mensaje3+0)
	ADDWFC      _aux0+1, 0 
	MOVWF       FSR0H 
	MOVLW       48
	SUBWF       POSTINC0+0, 0 
	MOVWF       _ptrCharMem+0 
	MOVLW       _mensaje3+0
	MOVWF       FARG_get_Array_Size_array+0 
	MOVLW       hi_addr(_mensaje3+0)
	MOVWF       FARG_get_Array_Size_array+1 
	CALL        _get_Array_Size+0, 0
	MOVF        R0, 0 
	MOVWF       _tamMsg+0 
L_main52:
;MyProject.c,341 :: 		if (erase_flag == 'z'){ ptrCharMem = mensaje4[aux0] - 0x30; tamMsg = get_Array_Size(mensaje4); }
	MOVF        _erase_flag+0, 0 
	XORLW       122
	BTFSS       STATUS+0, 2 
	GOTO        L_main53
	MOVLW       _mensaje4+0
	ADDWF       _aux0+0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(_mensaje4+0)
	ADDWFC      _aux0+1, 0 
	MOVWF       FSR0H 
	MOVLW       48
	SUBWF       POSTINC0+0, 0 
	MOVWF       _ptrCharMem+0 
	MOVLW       _mensaje4+0
	MOVWF       FARG_get_Array_Size_array+0 
	MOVLW       hi_addr(_mensaje4+0)
	MOVWF       FARG_get_Array_Size_array+1 
	CALL        _get_Array_Size+0, 0
	MOVF        R0, 0 
	MOVWF       _tamMsg+0 
	GOTO        L_main54
L_main53:
;MyProject.c,344 :: 		tamMsg = contador;
	MOVF        _contador+0, 0 
	MOVWF       _tamMsg+0 
;MyProject.c,345 :: 		ptrCharMem = (buffer_USB - 0x30);
	MOVLW       48
	SUBWF       _buffer_USB+0, 0 
	MOVWF       _ptrCharMem+0 
;MyProject.c,346 :: 		}
L_main54:
;MyProject.c,347 :: 		initPtrCharMem = ptrCharMem*7;
	MOVLW       7
	MULWF       _ptrCharMem+0 
	MOVF        PRODL+0, 0 
	MOVWF       _initPtrCharMem+0 
	MOVF        PRODH+0, 0 
	MOVWF       _initPtrCharMem+1 
;MyProject.c,348 :: 		getMap();
	CALL        _getMap+0, 0
;MyProject.c,350 :: 		if(flagVMemFull == 1 && invertido == 'n'){ visualizar(); }
	BTFSS       _flagVMemFull+0, BitPos(_flagVMemFull+0) 
	GOTO        L_main57
	MOVF        _invertido+0, 0 
	XORLW       110
	BTFSS       STATUS+0, 2 
	GOTO        L_main57
L__main66:
	CALL        _visualizar+0, 0
L_main57:
;MyProject.c,351 :: 		if(flagVMemFull == 1 && invertido == 's'){ visualizar_invertido(); }
	BTFSS       _flagVMemFull+0, BitPos(_flagVMemFull+0) 
	GOTO        L_main60
	MOVF        _invertido+0, 0 
	XORLW       115
	BTFSS       STATUS+0, 2 
	GOTO        L_main60
L__main65:
	CALL        _visualizar_invertido+0, 0
L_main60:
;MyProject.c,352 :: 		}
L_main49:
;MyProject.c,353 :: 		}
L_main48:
;MyProject.c,354 :: 		L_working = 1;
	BSF         RC7_bit+0, BitPos(RC7_bit+0) 
;MyProject.c,355 :: 		}
	GOTO        L_main46
;MyProject.c,357 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
