HM330XErrorCode print_result(const char* str, uint16_t value) {
  //if (NULL == str) {
  //  return ERROR_PARAM;
  //}
  //Serial.print(str); 1.0,2.5,10
  //Serial.println(value);
  //return NO_ERROR;
}

/*parse buf with 29 uint8_t-data*/
HM330XErrorCode parse_result(uint8_t* data) {
  uint16_t value = 0;
  if (NULL == data) {
    return ERROR_PARAM;
  }
  for (int i = 2; i < 5; i++) {
    value = (uint16_t) data[i * 2] << 8 | data[i * 2 + 1];
    Serial.print(value);
    Serial.print(",");

  }
  //return NO_ERROR;
}

HM330XErrorCode parse_result_value(uint8_t* data) {
  if (NULL == data) {
    return ERROR_PARAM;
  }
  for (int i = 0; i < 28; i++) {
    Serial.print(data[i], HEX);
    Serial.print("  ");
    if ((0 == (i) % 5) || (0 == i)) {
      Serial.println("");
    }
  }
  uint8_t sum = 0;
  for (int i = 0; i < 28; i++) {
    sum += data[i];
  }
  if (sum != data[28]) {
    Serial.println("wrong checkSum!!!!");
  }
  Serial.println("");
  return NO_ERROR;
}
