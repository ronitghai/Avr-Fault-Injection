int mixSignal;

void signal_callback(uint gpio, uint32_t events){
    mixSignal = ++mixSignal % 4;
    //asm("nop");
    if(!mixSignal) {
      //Serial.println("attack");
      digitalWrite(24, LOW);
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      digitalWrite(24, HIGH);
    
    //Serial.println("end attack");
  }
}

void setup() {
  Serial.ignoreFlowControl();
  Serial.begin(1800);
  Serial1.begin(1800);

  clock_gpio_init_int_frac(25, clk_usb, 48, 0);

  
  pinMode(11, INPUT);
  //gpio_set_irq_enabled_with_callback(11, GPIO_IRQ_EDGE_FALL, true, &signal_callback);

  pinMode(24, OUTPUT);
}

void loop() {
  mixSignal = -1;
  Serial1.flush();

  digitalWrite(24, HIGH);
  while(Serial1.available() < 16);

  String data = Serial1.readString();
  Serial.print(data);

  digitalWrite(24, LOW);
  delayMicroseconds(100000);
}