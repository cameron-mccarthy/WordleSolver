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
)

func main(){
	input := C.CString("slate")
	defer C.free(unsafe.Pointer(input))
	answer := C.CString("stilt")
	defer C.free(unsafe.Pointer(answer))
	fmt.Println(C.GoString(C.generate(answer, input)))
}

func todaysWordle(){
	resp, err := http.Get("https://www.nytimes.com/svc/wordle/v2/2025-07-07.json")
	if err != nil {
		fmt.Println("Error: ", err)
		return 
	}
	defer resp.Body.Close()
	body, _ := io.ReadAll(resp.Body)
	var data map[string]interface{}
	json.Unmarshal(body, &data)
	return
}