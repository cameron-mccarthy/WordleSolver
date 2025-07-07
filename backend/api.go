package main

/*
#cgo CFLAGS: -I.
#cgo LDFLAGS: -L. -lwordle
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"
*/
import "C"

import (
	"fmt"
	"encoding/json"
	"io"
	"net/http"
	"unsafe"
	"time"
)

func main(){
	currentTime := time.Now()
	answer := C.CString(todaysWordle(currentTime.Format("2006-01-02")))
	defer C.free(unsafe.Pointer(answer))
	answer := C.CString("stilt")
	defer C.free(unsafe.Pointer(input))
	

	fmt.Println(C.GoString(C.generate(answer, input)))
}

func todaysWordle(date string) string{
	resp, err := http.Get("https://www.nytimes.com/svc/wordle/v2/" + date + ".json")
	if err != nil {
		fmt.Println("Error: ", err)
		return ""
	}
	defer resp.Body.Close()
	body, _ := io.ReadAll(resp.Body)
	var data map[string]interface{}
	json.Unmarshal(body, &data)
	return data["solution"].(string)
}