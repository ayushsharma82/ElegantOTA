<template>
  <!-- eslint-disable max-len -->
  <main class="container">
    <div class="columns mt-3">
      <div class="col-12 mt-3 text-center">
        <img width="280px" alt="ElegantOTA" src="data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB2ZXJzaW9uPSIxLjEiIGlkPSJMYXllcl8xIiB4PSIwcHgiIHk9IjBweCIgdmlld0JveD0iMCAwIDI1NCA4MyIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgMjU0IDgzOyI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6IzJFMzAzNDt9Cgkuc3Qxe2ZpbGw6IzQ4OEVGRjt9Cjwvc3R5bGU+CjxnIGlkPSJfeDMwX2I3NDI0NjctMjdlYS1hZTNmLTdjZmEtY2EwZTEwYWMwNGU3IiB0cmFuc2Zvcm09Im1hdHJpeCgyLjIsMCwwLDIuMiwxMDMuODg3NjQxNjY4MzE5NywxMzIuMzU1OTk2MDM2NTI5NTUpIj4KCTxwYXRoIGNsYXNzPSJzdDAiIGQ9Ik0tNi4xLTQ1LjR2LTFILTEzdjkuM2g2Ljh2LTFoLTUuOHYtMy4xaDUuMnYtMWgtNS4ydi0zLjFILTYuMXogTS0zLjYtNDdoLTEuMXY5LjhoMS4xVi00N3ogTTEuMy0zOCAgIGMtMS40LDAtMi4zLTEtMi41LTIuMmg1Ljl2LTAuNGMwLTItMS4zLTMuNi0zLjUtMy42cy0zLjUsMS42LTMuNSwzLjZTLTAuOC0zNywxLjMtMzdDMy0zNyw0LTM3LjksNC41LTM5LjJIMy4zICAgQzMtMzguNSwyLjMtMzgsMS4zLTM4eiBNMS4yLTQzLjNjMS4zLDAsMi4yLDAuOSwyLjQsMi4xaC00LjhDLTAuOS00Mi40LTAuMS00My4zLDEuMi00My4zeiBNMTEuNS00NC4ydjEuMSAgIGMtMC41LTAuOC0xLjMtMS4yLTIuNS0xLjJjLTIsMC0zLjQsMS42LTMuNCwzLjZjMCwyLDEuMywzLjYsMy40LDMuNmMxLjIsMCwyLTAuNSwyLjUtMS4zdjFjMCwxLjQtMC43LDIuMi0yLjMsMi4yICAgYy0xLjEsMC0xLjgtMC40LTItMS4xSDUuOWMwLjQsMS4yLDEuNSwyLDMuMywyYzIuMSwwLDMuMy0xLjEsMy4zLTMuMXYtNi44SDExLjV6IE05LjEtMzguMWMtMS42LDAtMi41LTEuMi0yLjUtMi42ICAgYzAtMS40LDAuOS0yLjYsMi41LTIuNmMxLjUsMCwyLjQsMS4yLDIuNCwyLjZDMTEuNS0zOS4zLDEwLjYtMzguMSw5LjEtMzguMXogTTE3LjMtNDQuM2MtMiwwLTMuNCwxLjYtMy40LDMuNnMxLjMsMy42LDMuNCwzLjYgICBjMS4yLDAsMi0wLjUsMi41LTEuMnYxLjFoMXYtN2gtMXYxLjFDMTkuMy00My44LDE4LjQtNDQuMywxNy4zLTQ0LjN6IE0xNy40LTM4Yy0xLjYsMC0yLjUtMS4yLTIuNS0yLjdjMC0xLjQsMC45LTIuNywyLjUtMi43ICAgYzEuNiwwLDIuNCwxLjIsMi40LDIuN0MxOS44LTM5LjIsMTktMzgsMTcuNC0zOHogTTIyLjctNDQuMnY3aDF2LTRjMC0xLjMsMS0yLjEsMi4xLTIuMWMxLjIsMCwyLDAuOCwyLDIuMXY0aDF2LTQuMSAgIGMwLTItMS4zLTMtMi44LTNjLTEuMSwwLTEuOCwwLjUtMi4zLDEuMnYtMS4xSDIyLjd6IE0zMi4yLTM3LjJ2LTYuMWgxLjZ2LTAuOWgtMS42di0yLjVoLTEuMXYyLjVoLTEuNHYwLjloMS40djYuMUgzMi4yeiAgICBNMzkuMy00Ni41Yy0yLjgsMC00LjcsMi4xLTQuNyw0LjhjMCwyLjYsMS45LDQuNyw0LjcsNC43czQuNy0yLjEsNC43LTQuN0M0NC00NC40LDQyLjEtNDYuNSwzOS4zLTQ2LjV6IE0zOS4zLTM4LjEgICBjLTIuMywwLTMuNy0xLjYtMy43LTMuN2MwLTIuMSwxLjQtMy43LDMuNy0zLjdzMy43LDEuNiwzLjcsMy43QzQzLTM5LjcsNDEuNi0zOC4xLDM5LjMtMzguMXogTTUxLjktNDYuNGgtNy41djFoMy4ydjguM2gxdi04LjMgICBoMy4yVi00Ni40eiBNNTYuNS00Ni40aC0xLjNsLTMuOSw5LjNoMS4ybDEuMS0yLjdoNC42bDEuMSwyLjdoMS4yTDU2LjUtNDYuNHogTTU0LTQwLjhsMS45LTQuNWwxLjksNC41SDU0eiIvPgo8L2c+CjxnIGlkPSJkYzY4OGQxZi1hMDY2LWI3ZTctOGFiYy0xMTVmYTQwZTk0NDUiIHRyYW5zZm9ybT0ibWF0cml4KDAuMjI1NTIwNTc0ODgyOTcxMTEsMCwwLDAuMjI1NTIwNTc0ODgyOTcxMTEsMzQuNTIyNzQzOTgxNjY2ODU2LDExNy4wMTc3NDQ5NjcyNzM1KSI+Cgk8cGF0aCBjbGFzcz0ic3QxIiBkPSJNMTE5LTM0Ny42YzUuNywwLDcuOCw2LjYsNC41LDEwLjhjLTcuMiw4LjQtMTQuNCwxNi41LTIxLjYsMjQuOWMtMi4xLDIuNC02LjYsMi40LTksMCAgIGMtNy4yLTguNC0xNC40LTE2LjUtMjEuNi0yNC45Yy00LjUtNS4xLDEuMi0xMi4zLDYuMy0xMC44aDEzLjJjLTcuMi0yOC44LTI5LjEtNTIuNS01OC44LTU5LjFjLTUuNy0xLjItMTEuNC0xLjgtMTcuMS0xLjggICBjLTI4LjgsMC01NS41LDE1LjktNjkuNiw0MmMtMy45LDcuMi0xNC43LDAuOS0xMC44LTYuM2MxOS4yLTM0LjgsNTkuNC01NC45LDk4LjctNDYuMmMzNS40LDcuNSw2MywzNiw3MC4yLDcxLjQgICBDMTAzLjQtMzQ3LjYsMTE5LTM0Ny42LDExOS0zNDcuNnogTS04My4yLTMwOS4yYy01LjcsMC03LjgtNi42LTQuNS0xMC44YzcuMi04LjQsMTQuNC0xNi41LDIxLjYtMjQuOWMyLjEtMi40LDYuNi0yLjQsOSwwICAgYzcuMiw4LjQsMTQuNCwxNi41LDIxLjYsMjQuOWM0LjUsNS4xLTEuMiwxMi4zLTYuMywxMC44SC01NWM3LjIsMjguOCwyOS4xLDUyLjUsNTguOCw1OS4xYzUuNywxLjIsMTEuNCwxLjgsMTcuMSwxLjggICBjMjguOCwwLDU1LjUtMTUuOSw2OS42LTQyYzMuOS03LjIsMTQuNy0wLjksMTAuOCw2LjNjLTE5LjIsMzUuMS01OS40LDU1LjItOTguNyw0Ni41Yy0zNS40LTcuOC02My4zLTM2LjMtNzAuNS03MS43SC04My4yeiIvPgo8L2c+Cjwvc3ZnPgo=">
      </div>
      <div class="col-12 p-centered"></div>
      <div class="col-12 mt-3 p-centered" v-if="loading">
        <div class="col-3 col-sm-10 p-centered">
          <div class="loading loading-lg mt-3"></div>
        </div>
      </div>
      <transition name="fade" mode="out-in">
        <div class="col-12 mt-3 pt-2 p-centered" v-if="!loading && !uploading && OTAError !== null" key="error">
          <div class="col-3 col-sm-9 col-md-6 p-centered text-center">
            <svg width="32px" height="32px" style="vertical-align: middle;" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
              <g stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                <circle id="Oval-5" fill="#DF4759" opacity="0.3" cx="12" cy="12" r="10"></circle>
                <rect id="Rectangle-9" fill="#DF4759" x="11" y="7" width="2" height="8" rx="1"></rect>
                <rect id="Rectangle-9-Copy" fill="#DF4759" x="11" y="16" width="2" height="2" rx="1"></rect>
              </g>
            </svg>
            <span style="vertical-align: middle;" class="ml-2"> {{ OTAError }} </span>
            <br>
            <br>
            <div class="mt-3">
              <button class="btn btn-light mr-2" @click="clear">
                <svg xmlns="http://www.w3.org/2000/svg" class="pt-1" width="16px" height="16px" viewBox="0 0 24 24">
                  <g data-name="Layer 2">
                    <g data-name="arrow-back">
                      <rect width="24" height="24" transform="rotate(90 12 12)" opacity="0" />
                      <path
                        fill="currentColor"
                        d="M19 11H7.14l3.63-4.36a1 1 0 1 0-1.54-1.28l-5 6a1.19 1.19 0 0 0-.09.15c0 .05 0 .08-.07.13A1 1 0 0 0 4 12a1 1 0 0 0 .07.36c0 .05 0 .08.07.13a1.19 1.19 0 0 0 .09.15l5 6A1 1 0 0 0 10 19a1 1 0 0 0 .64-.23 1 1 0 0 0 .13-1.41L7.14 13H19a1 1 0 0 0 0-2z" />
                    </g>
                  </g>
                </svg>
                Back
              </button>
              <button class="btn btn-primary ml-2" @click="retryOTA">
                <svg xmlns="http://www.w3.org/2000/svg" class="pt-1" width="16px" height="16px" viewBox="0 0 24 24">
                  <g data-name="Layer 2">
                    <g data-name="refresh">
                      <rect width="24" height="24" opacity="0" />
                      <path
                        fill="currentColor"
                        d="M20.3 13.43a1 1 0 0 0-1.25.65A7.14 7.14 0 0 1 12.18 19 7.1 7.1 0 0 1 5 12a7.1 7.1 0 0 1 7.18-7 7.26 7.26 0 0 1 4.65 1.67l-2.17-.36a1 1 0 0 0-1.15.83 1 1 0 0 0 .83 1.15l4.24.7h.17a1 1 0 0 0 .34-.06.33.33 0 0 0 .1-.06.78.78 0 0 0 .2-.11l.09-.11c0-.05.09-.09.13-.15s0-.1.05-.14a1.34 1.34 0 0 0 .07-.18l.75-4a1 1 0 0 0-2-.38l-.27 1.45A9.21 9.21 0 0 0 12.18 3 9.1 9.1 0 0 0 3 12a9.1 9.1 0 0 0 9.18 9A9.12 9.12 0 0 0 21 14.68a1 1 0 0 0-.7-1.25z" />
                    </g>
                  </g>
                </svg>
                Retry
              </button>
            </div>
          </div>
        </div>
        <div class="col-12 mt-3 pt-2 p-centered" v-else-if="!loading && !uploading && OTASuccess" key="success">
          <div class="col-3 col-sm-9 col-md-6 p-centered text-center">
            <svg width="32px" height="32px" style="vertical-align: middle;" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
              <g stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                <circle id="Oval-5" fill="#42BA96" opacity="0.3" cx="12" cy="12" r="10"></circle>
                <path d="M16.7689447,7.81768175 C17.1457787,7.41393107 17.7785676,7.39211077 18.1823183,7.76894473 C18.5860689,8.1457787 18.6078892,8.77856757 18.2310553,9.18231825 L11.2310553,16.6823183 C10.8654446,17.0740439 10.2560456,17.107974 9.84920863,16.7592566 L6.34920863,13.7592566 C5.92988278,13.3998345 5.88132125,12.7685345 6.2407434,12.3492086 C6.60016555,11.9298828 7.23146553,11.8813212 7.65079137,12.2407434 L10.4229928,14.616916 L16.7689447,7.81768175 Z" id="Path-92" fill="#42BA96"></path>
              </g>
            </svg>
            <span style="vertical-align: middle;" class="ml-2 mb-2"> OTA Success </span>
            <br>
            <br>
            <button class="btn btn-primary mt-3" @click="clear">
              <svg xmlns="http://www.w3.org/2000/svg" class="pt-1" width="16px" height="16px" viewBox="0 0 24 24">
                <g data-name="Layer 2">
                  <g data-name="arrow-back">
                    <rect width="24" height="24" transform="rotate(90 12 12)" opacity="0" />
                    <path
                      fill="currentColor"
                      d="M19 11H7.14l3.63-4.36a1 1 0 1 0-1.54-1.28l-5 6a1.19 1.19 0 0 0-.09.15c0 .05 0 .08-.07.13A1 1 0 0 0 4 12a1 1 0 0 0 .07.36c0 .05 0 .08.07.13a1.19 1.19 0 0 0 .09.15l5 6A1 1 0 0 0 10 19a1 1 0 0 0 .64-.23 1 1 0 0 0 .13-1.41L7.14 13H19a1 1 0 0 0 0-2z" />
                  </g>
                </g>
              </svg>
              Back
            </button>
          </div>
        </div>
        <div class="col-12 mt-3 p-centered" v-else-if="!loading && !uploading" key="otainput">
          <div class="col-3 col-sm-9 col-md-6 p-centered">
            <div class="form-group pt-2 mt-2">
              <label class="form-radio form-inline mr-2">
                <input type="radio" name="firmwaretype" for="firmwaretype" value="firmware" v-model="type"><i class="form-icon"></i> Firmware
              </label>
              <label class="form-radio form-inline ml-2">
                <input type="radio" name="firmwaretype" for="firmwaretype" value="filesystem" v-model="type"><i class="form-icon"></i> Filesystem
              </label>
            </div>
            <div class="form-group pt-2 mt-3">
              <input class="form-input file-input" type="file" ref="file" accept=".bin,.bin.gz" @change="uploadOTA">
            </div>
          </div>
        </div>
      </transition>
      <transition name="fade" mode="out-in">
        <div class="col-12 mt-3 mb-2 pt-2 p-centered" v-if="!loading && uploading">
          <div class="col-2 mt-3 mb-2 col-sm-7 col-md-4 text-right p-centered">
            <div class="bar mt-3 bar-sm">
              <div class="bar-item tooltip" :data-tooltip="progress+'%'" :style="{ width: progress+'%' }"></div>
            </div>
            <div class="pt-2">{{progress}}%</div>
          </div>
        </div>
      </transition>
      <div class="col-12 mt-3 p-centered"></div>
    </div>
    <transition name="fade" mode="out-in">
      <div class="columns mt-3" v-if="!loading">
        <div class="col-12 text-center">
          <span class="label label-rounded mr-2">{{ deviceData.id }}</span> - <span class="label label-rounded label-primary ml-2">{{ deviceData.hardware }}</span>
        </div>
      </div>
    </transition>
    <transition name="slide-fade" mode="out-in" appear>
      <div class="coffee-link" v-if="!loading">
        <div class="card">
          <div class="card-body mt-2 mr-1">
            <a href="https://www.buymeacoffee.com/6QGVpSj" target="_blank">
              <svg xmlns="http://www.w3.org/2000/svg" width="180px" xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 0 901.38 180.48"><defs><clipPath id="a" transform="translate(-277.93 -399.55)"><path d="M463,416.14v-3.7a3.71,3.71,0,0,0-3.7-3.71h-1.23a3.7,3.7,0,0,0-3.7,3.71v3.7h-3.7a3.69,3.69,0,0,0-3.7,3.7v1.23a3.7,3.7,0,0,0,3.7,3.7h3.7v3.7a3.7,3.7,0,0,0,3.7,3.7h1.23a3.7,3.7,0,0,0,3.7-3.7v-3.7h3.7a3.7,3.7,0,0,0,3.7-3.7v-1.23a3.69,3.69,0,0,0-3.7-3.7Z" style="fill:none;clip-rule:evenodd"/></clipPath><clipPath id="b" transform="translate(-277.93 -399.55)"><rect width="1443.51" height="962.34" style="fill:none"/></clipPath><clipPath id="c" transform="translate(-277.93 -399.55)"><polygon points="383.22 435.09 344.43 434.86 363.48 555.88 367.63 555.88 405.73 555.88 409.89 555.88 428.94 434.86 383.22 435.09" style="fill:none;clip-rule:evenodd"/></clipPath><clipPath id="e" transform="translate(-277.93 -399.55)"><polygon points="383.22 435.09 344.43 434.86 363.48 555.88 367.63 555.88 396.03 555.88 400.19 555.88 419.24 434.86 383.22 435.09" style="fill:none;clip-rule:evenodd"/></clipPath><clipPath id="g" transform="translate(-277.93 -399.55)"><rect x="333.34" y="423.7" width="100.1" height="11.16" style="fill:none"/></clipPath><clipPath id="i" transform="translate(-277.93 -399.55)"><polygon points="414.04 405.56 390.15 405.56 375.94 405.56 352.05 405.56 344.77 422.3 375.94 422.3 390.15 422.3 421.32 422.3 414.04 405.56" style="fill:none;clip-rule:evenodd"/></clipPath><clipPath id="k" transform="translate(-277.93 -399.55)"><polygon points="430.32 469.04 384.69 469.04 381.4 469.04 335.77 469.04 344.3 517.16 383.05 516.75 421.79 517.16 430.32 469.04" style="fill:none;clip-rule:evenodd"/></clipPath><clipPath id="m" transform="translate(-277.93 -399.55)"><circle cx="300.53" cy="451.42" r="14.23" transform="translate(-167.53 725.33) rotate(-86.68)" style="fill:none"/></clipPath><clipPath id="o" transform="translate(-277.93 -399.55)"><circle cx="448.68" cy="494.11" r="6.7" style="fill:none"/></clipPath><clipPath id="q" transform="translate(-277.93 -399.55)"><circle cx="323.13" cy="532.61" r="6.7" style="fill:none"/></clipPath><clipPath id="s" transform="translate(-277.93 -399.55)"><path d="M538.76,494.1a19.55,19.55,0,0,0-4.07-5.83,15.42,15.42,0,0,0-6.07-3.65,13.19,13.19,0,0,0,3-3.88,34.63,34.63,0,0,0,2.52-5.79,32.14,32.14,0,0,0,1.42-6.3,13.88,13.88,0,0,0-.29-5.46,18,18,0,0,0-13.13-13.37A26.24,26.24,0,0,0,512,449.3a53.94,53.94,0,0,0-11.34,2.8,5.94,5.94,0,0,1,.1-1,6.33,6.33,0,0,0,.09-1.09,3,3,0,0,0-1.42-2.46,6.46,6.46,0,0,0-3.27-1.23,5.92,5.92,0,0,0-3.6.8,5.45,5.45,0,0,0-2.42,3.65q-.76,8.53-1.52,17.73T487,487.09q-.86,9.39-1.71,18.63t-1.7,17.78a7.6,7.6,0,0,0,1.42,4,4.42,4.42,0,0,0,2.65,1.71,5.1,5.1,0,0,0,3.18-.52,7.13,7.13,0,0,0,2.89-2.8,24,24,0,0,0,8.54,2.7,37.77,37.77,0,0,0,9.62,0,44.66,44.66,0,0,0,9.62-2.32,40.59,40.59,0,0,0,8.63-4.27,28.51,28.51,0,0,0,6.55-5.83,17.1,17.1,0,0,0,3.5-7.06,24.92,24.92,0,0,0,.48-7.78A22.5,22.5,0,0,0,538.76,494.1ZM499.6,463.29a23.27,23.27,0,0,1,4.79-2.18,29.54,29.54,0,0,1,5.74-1.33,25,25,0,0,1,5.73-.09,11.78,11.78,0,0,1,4.93,1.56A7.76,7.76,0,0,1,524,465a11.79,11.79,0,0,1,.57,6.11,8.63,8.63,0,0,1-2.32,5,16.67,16.67,0,0,1-4.75,3.42,31.17,31.17,0,0,1-5.92,2.18,51.83,51.83,0,0,1-6,1.18c-1.93.25-3.61.41-5,.48s-2.35.09-2.8.09Zm28.92,44.23a18,18,0,0,1-4.69,5.69,25.37,25.37,0,0,1-7,3.94,34.9,34.9,0,0,1-8,2,27,27,0,0,1-7.83-.09,15.08,15.08,0,0,1-6.44-2.51l2-20.77q2.74-.94,6.92-1.94a61.43,61.43,0,0,1,8.58-1.42,36.13,36.13,0,0,1,8.34.09,11.52,11.52,0,0,1,6.21,2.51,12.4,12.4,0,0,1,2.09,2.47,6.55,6.55,0,0,1,1,2.75A12.15,12.15,0,0,1,528.52,507.52Z" style="fill:none;clip-rule:evenodd"/></clipPath><clipPath id="u" transform="translate(-277.93 -399.55)"><path d="M663.4,503a4.68,4.68,0,0,0-3.13-1.61c-1.23-.13-2.48.57-3.74,2.08a22.23,22.23,0,0,1-3.13,4.36,40,40,0,0,1-3.94,3.8,46.8,46.8,0,0,1-3.88,2.94c-1.24.82-2.2,1.42-2.9,1.8a59.8,59.8,0,0,1-.42-6.55q-.06-3.49.14-7.11a88.14,88.14,0,0,1,1.19-10.33,68.28,68.28,0,0,1,2.6-10.24,7.09,7.09,0,0,0-1.23-4.32,5,5,0,0,0-6.59-1.61,7.61,7.61,0,0,0-3.18,3.27q-1.12,3.13-2.6,7t-3.32,7.92a79.91,79.91,0,0,1-4.13,7.82,40.35,40.35,0,0,1-5,6.73,21.5,21.5,0,0,1-5.87,4.6,13.07,13.07,0,0,1-6.88,1.47A3.7,3.7,0,0,1,605,512.5a17.52,17.52,0,0,1-.9-5.22,43.43,43.43,0,0,1,.28-6.87c.29-2.5.66-5,1.14-7.44s1-4.81,1.56-7,1.11-4.08,1.61-5.59q1.14-2.76,0-4.6a5.44,5.44,0,0,0-3.12-2.47,7,7,0,0,0-4.18,0,4.83,4.83,0,0,0-3.13,2.94,75.84,75.84,0,0,0-2.94,8.72,92.34,92.34,0,0,0-2.13,10,74.57,74.57,0,0,0-.9,10.24c0,.22,0,.43,0,.65a42.74,42.74,0,0,1-3.94,8.31c-1.62,2.4-3.43,3.44-5.46,3.13a3.36,3.36,0,0,1-1.75-2.66,21,21,0,0,1-.29-5.12q.15-3,.72-6.87t1.42-8c.57-2.75,1.17-5.51,1.8-8.3s1.2-5.4,1.71-7.87a7,7,0,0,0-2-5.07,6.12,6.12,0,0,0-5.16-1.37,7.56,7.56,0,0,0-3.37,2.46,12.43,12.43,0,0,0-1.76,3.89c-.25.82-.63,2.47-1.13,4.93s-1.16,5.3-2,8.49-1.72,6.52-2.79,10a71.82,71.82,0,0,1-3.61,9.43,26.55,26.55,0,0,1-4.36,6.78q-2.37,2.56-5.12,2.09c-1-.19-1.66-1.23-1.94-3.13a33.41,33.41,0,0,1-.15-7,90.65,90.65,0,0,1,1.14-9.14c.57-3.32,1.15-6.47,1.76-9.44s1.15-5.6,1.66-7.87.85-3.79,1-4.55a7.25,7.25,0,0,0-1.23-4.41,5.32,5.32,0,0,0-3-2.09,5.24,5.24,0,0,0-3.6.48,7.56,7.56,0,0,0-3.18,3.27c-.32,1.71-.73,3.68-1.23,5.93s-1,4.55-1.47,6.92-.92,4.69-1.33,7-.71,4.26-.9,6c-.13,1.33-.27,3-.43,4.88s-.24,4-.24,6.12a42.79,42.79,0,0,0,.48,6.4,21,21,0,0,0,1.71,5.83,11.44,11.44,0,0,0,3.46,4.36,9.94,9.94,0,0,0,5.64,1.9,19.72,19.72,0,0,0,6.12-.52,15.17,15.17,0,0,0,4.74-2.23,20.62,20.62,0,0,0,3.88-3.61,55.78,55.78,0,0,0,3.46-4.55,14.32,14.32,0,0,0,4.18,5.6,11.07,11.07,0,0,0,5.4,2.37,11.34,11.34,0,0,0,5.79-.81,13.63,13.63,0,0,0,5.31-4,29.26,29.26,0,0,0,2.94-3.94,18.65,18.65,0,0,0,1.27,1.95,11.75,11.75,0,0,0,6.31,4.17,18.64,18.64,0,0,0,8.34.38,26.37,26.37,0,0,0,7.78-2.75,36.1,36.1,0,0,0,6.87-4.78A43.2,43.2,0,0,0,631.4,513c-.06,1.46-.09,2.83-.09,4.13s0,2.7-.1,4.22a53.92,53.92,0,0,0-9,8,64,64,0,0,0-7.4,9.91,53.4,53.4,0,0,0-5,10.67,31.11,31.11,0,0,0-1.76,10.1,15.54,15.54,0,0,0,2.23,8.2,12.12,12.12,0,0,0,7.11,5,13.34,13.34,0,0,0,9,.1,16.52,16.52,0,0,0,6.78-5,29,29,0,0,0,4.74-8.48,69.49,69.49,0,0,0,2.94-10.39,73.65,73.65,0,0,0,1.38-10.61,75.66,75.66,0,0,0,0-9.3,40.85,40.85,0,0,0,13.36-8.63,54.82,54.82,0,0,0,8.63-11,4.31,4.31,0,0,0,.72-3.41A6.63,6.63,0,0,0,663.4,503m-32.14,41.15q-.53,3.12-1.47,6.59a43.41,43.41,0,0,1-2.23,6.31,18,18,0,0,1-2.84,4.59,3.67,3.67,0,0,1-3.37,1.47,2.06,2.06,0,0,1-1.8-1.8,10.56,10.56,0,0,1,0-4A29,29,0,0,1,621,552a45.52,45.52,0,0,1,2.65-5.92,47,47,0,0,1,3.56-5.65,25.35,25.35,0,0,1,4.17-4.5,5.06,5.06,0,0,1,.43,2.85,39.49,39.49,0,0,1-.57,5.4" style="fill:none;clip-rule:evenodd"/></clipPath><clipPath id="w" transform="translate(-277.93 -399.55)"><path d="M815.87,500.84a5.37,5.37,0,0,0-3-.1,2.46,2.46,0,0,0-1.8,2,27.53,27.53,0,0,1-2.42,6.21,32.42,32.42,0,0,1-4.07,6,30.54,30.54,0,0,1-5.45,5,20.58,20.58,0,0,1-6.36,3.13,8.57,8.57,0,0,1-5.5.24,7,7,0,0,1-3.46-2.75,13.48,13.48,0,0,1-1.85-4.7,32.92,32.92,0,0,1-.66-5.69,17,17,0,0,0,9.62-1.94,22.67,22.67,0,0,0,7.16-6.16,28,28,0,0,0,4.46-8.63,36.45,36.45,0,0,0,1.71-9.53,17.09,17.09,0,0,0-1.33-7.54,11.78,11.78,0,0,0-3.84-4.79,11.17,11.17,0,0,0-5.55-2,15,15,0,0,0-6.35.85,15.55,15.55,0,0,0-6.59,4.32,26.72,26.72,0,0,0-4.5,6.92,43.42,43.42,0,0,0-2.85,8.49,76.62,76.62,0,0,0-1.52,9c-.28,2.64-.43,5.16-.49,7.59-.13.31-.26.61-.41.94a57.18,57.18,0,0,1-3.41,6.59,24.69,24.69,0,0,1-4.32,5.41,5.11,5.11,0,0,1-4.93,1.51c-1-.25-1.56-1.42-1.65-3.5a53.19,53.19,0,0,1,.33-7.78c.31-3.1.68-6.45,1.09-10.05a91.48,91.48,0,0,0,.61-10.34,21.36,21.36,0,0,0-1.61-8.2,18.16,18.16,0,0,0-4.41-6.54,14,14,0,0,0-6.49-3.46,12.13,12.13,0,0,0-8,1.14,16.67,16.67,0,0,0-6.78,5.59,70.23,70.23,0,0,0-4.6,7.59,22.32,22.32,0,0,0-2.22-5.65,18.26,18.26,0,0,0-3.61-4.55,16.42,16.42,0,0,0-4.78-3,14.59,14.59,0,0,0-5.6-1.09,12.57,12.57,0,0,0-5.26,1.09,18.42,18.42,0,0,0-4.41,2.8,24,24,0,0,0-3.61,3.84,46.5,46.5,0,0,0-2.84,4.21c-.13-1.64-.27-3.08-.43-4.31a10.1,10.1,0,0,0-.85-3.13,4.36,4.36,0,0,0-1.75-1.94,6.51,6.51,0,0,0-3.23-.67,5.53,5.53,0,0,0-2.08.43,5.87,5.87,0,0,0-1.85,1.19,4.88,4.88,0,0,0-1.47,4.36,13.89,13.89,0,0,0,.52,2.51,35.38,35.38,0,0,1,.81,3.84q.38,2.37.61,5.74t.14,8.25q-.09,4.88-.71,11.42t-1.94,15.17a3.36,3.36,0,0,0,1.52,3.23,7.91,7.91,0,0,0,8,.66,4,4,0,0,0,2.23-3.32q.29-4.46,1.09-9.48c.53-3.35,1.2-6.67,2-10s1.69-6.41,2.7-9.38A50.14,50.14,0,0,1,703,490a24.19,24.19,0,0,1,3.84-5.45,5.81,5.81,0,0,1,4.17-2,4.58,4.58,0,0,1,4.12,2.41,17.35,17.35,0,0,1,2.09,6.21,49,49,0,0,1,.57,8.3c0,3-.16,5.9-.38,8.68s-.47,5.26-.76,7.44-.49,3.68-.61,4.51a4.16,4.16,0,0,0,1.65,3.46,7.31,7.31,0,0,0,3.7,1.51,6.2,6.2,0,0,0,3.84-.76,4.13,4.13,0,0,0,2.09-3.36q.95-6.83,2.6-13.7a96.22,96.22,0,0,1,3.8-12.33A37.58,37.58,0,0,1,738.5,486q2.61-3.47,5.55-3.46c1,0,1.78.69,2.32,2.08a16.19,16.19,0,0,1,.8,5.69,36.62,36.62,0,0,1-.42,5.45q-.43,2.81-1,5.79t-1,6.11a47.62,47.62,0,0,0-.43,6.55,38.11,38.11,0,0,0,.47,5.5,21.08,21.08,0,0,0,1.81,5.92,13.65,13.65,0,0,0,3.65,4.74,8.89,8.89,0,0,0,5.92,2,19.33,19.33,0,0,0,9.58-2.33,24,24,0,0,0,7.16-6.06l.3-.4c.15.36.28.76.46,1.11a15.59,15.59,0,0,0,5.54,6.44,16.38,16.38,0,0,0,8.25,2.52,27.06,27.06,0,0,0,10.34-1.76,28.34,28.34,0,0,0,7.25-3.79,27.28,27.28,0,0,0,5.55-5.55,44.36,44.36,0,0,0,4.5-7.53q2-4.28,4.13-9.77a2.8,2.8,0,0,0-.71-2.7,5.79,5.79,0,0,0-2.66-1.66M783,497a46.22,46.22,0,0,1,.85-4.6,38,38,0,0,1,1.42-4.69,18.35,18.35,0,0,1,2-3.94,7.6,7.6,0,0,1,2.42-2.37,2.41,2.41,0,0,1,2.61.14c1,.57,1.53,1.77,1.75,3.61a13.93,13.93,0,0,1-.66,5.88,15.46,15.46,0,0,1-3.56,5.87,12.34,12.34,0,0,1-6.92,3.61A13.38,13.38,0,0,1,783,497" style="fill:none;clip-rule:evenodd"/></clipPath><clipPath id="y" transform="translate(-277.93 -399.55)"><path d="M901.11,497.52a4,4,0,0,0-3-.33c-1,.28-1.79,1.25-2.23,2.89a31.68,31.68,0,0,1-1.7,6.26,39.68,39.68,0,0,1-3.28,6.82,21.44,21.44,0,0,1-4.45,5.36,7.34,7.34,0,0,1-5.36,1.94,3.69,3.69,0,0,1-3.32-2.41,14.94,14.94,0,0,1-1-5.6,42,42,0,0,1,.66-7.58q.71-4.22,1.71-8.4t2-8q1-3.84,1.7-6.49a4.24,4.24,0,0,0-.47-4,6.79,6.79,0,0,0-3.08-2.37,6.91,6.91,0,0,0-3.75-.38,2.93,2.93,0,0,0-2.47,2q-5.6-4.85-10.76-5.22a15.72,15.72,0,0,0-9.53,2.28,25.18,25.18,0,0,0-7.72,7.68A49.19,49.19,0,0,0,837,505a33.3,33.3,0,0,0,.8,11.24,17.23,17.23,0,0,0,4.7,8.29q3.36,3.23,9.15,3.23a12.07,12.07,0,0,0,4.93-1,24,24,0,0,0,4.36-2.46,26.32,26.32,0,0,0,3.51-3q1.51-1.56,2.37-2.61a16.45,16.45,0,0,0,2.18,5.79,15,15,0,0,0,3.46,3.88,13.42,13.42,0,0,0,4.08,2.23,12.8,12.8,0,0,0,4.12.71,13.36,13.36,0,0,0,8.35-3,34,34,0,0,0,7-7.44,47.29,47.29,0,0,0,5.08-9.3,43.27,43.27,0,0,0,2.65-8.67,3.1,3.1,0,0,0-.24-3,5.81,5.81,0,0,0-2.37-2.32m-33.7-7.26q-.48,2.81-1.28,6.17c-.54,2.24-1.22,4.57-2,7a31.33,31.33,0,0,1-3,6.49,16.25,16.25,0,0,1-4.12,4.6,7.55,7.55,0,0,1-5.36,1.42,3,3,0,0,1-2.32-2.08,13.15,13.15,0,0,1-.86-4.84,37,37,0,0,1,.53-6.45,39.11,39.11,0,0,1,1.75-6.87,34,34,0,0,1,2.89-6.21,14.1,14.1,0,0,1,3.94-4.41,7.83,7.83,0,0,1,4.88-1.47,9.66,9.66,0,0,1,5.69,2.65c-.13.83-.35,2.17-.66,4" style="fill:none;clip-rule:evenodd"/></clipPath><clipPath id="aa" transform="translate(-277.93 -399.55)"><path d="M1172.49,502.5a5.79,5.79,0,0,0-2.66-1.66,5.33,5.33,0,0,0-3-.1,2.48,2.48,0,0,0-1.81,2,28,28,0,0,1-2.41,6.21,32.57,32.57,0,0,1-4.08,6,30.23,30.23,0,0,1-5.45,5,20.42,20.42,0,0,1-6.35,3.13,8.61,8.61,0,0,1-5.51.24,7,7,0,0,1-3.46-2.75,13.48,13.48,0,0,1-1.85-4.7,33.93,33.93,0,0,1-.66-5.69,17,17,0,0,0,9.63-1.94,22.89,22.89,0,0,0,7.16-6.16,28.16,28.16,0,0,0,4.45-8.63,36.45,36.45,0,0,0,1.71-9.53,17.09,17.09,0,0,0-1.33-7.54,11.78,11.78,0,0,0-3.84-4.79,11.17,11.17,0,0,0-5.55-2,15,15,0,0,0-6.35.85,15.55,15.55,0,0,0-6.59,4.32,27,27,0,0,0-4.5,6.92,43.64,43.64,0,0,0-2.85,8.49,74.51,74.51,0,0,0-1.51,9q-.46,4.27-.52,8.19c-.24.52-.49,1.05-.77,1.57a32,32,0,0,1-4.07,6,30,30,0,0,1-5.46,5,20.31,20.31,0,0,1-6.35,3.13,8.57,8.57,0,0,1-5.5.24,7,7,0,0,1-3.46-2.75,13.48,13.48,0,0,1-1.85-4.7,32.92,32.92,0,0,1-.66-5.69,17,17,0,0,0,9.62-1.94,22.78,22.78,0,0,0,7.16-6.16,28,28,0,0,0,4.46-8.63A36,36,0,0,0,1120,484a17,17,0,0,0-1.32-7.54,11.78,11.78,0,0,0-3.84-4.79,11.2,11.2,0,0,0-5.55-2,15,15,0,0,0-6.35.85,15.49,15.49,0,0,0-6.59,4.32,27,27,0,0,0-4.51,6.92,43.63,43.63,0,0,0-2.84,8.49,76.62,76.62,0,0,0-1.52,9c-.18,1.66-.3,3.26-.39,4.84-.61.52-1.2,1-1.84,1.56a57.84,57.84,0,0,1-6.87,4.79,43.2,43.2,0,0,1-7.49,3.51,29.93,29.93,0,0,1-8,1.65l5.88-63a3.79,3.79,0,0,0-.57-3.5,5.73,5.73,0,0,0-2.94-2.09,6.17,6.17,0,0,0-3.84.09,6.09,6.09,0,0,0-3.36,3c-.45,2.4-.9,5.69-1.38,9.86s-1,8.72-1.42,13.65-1,10-1.42,15.27-.89,10.15-1.23,14.7c0,.2,0,.38-.05.58-.55.47-1.09.94-1.66,1.41a57.15,57.15,0,0,1-6.88,4.79,42.86,42.86,0,0,1-7.49,3.51,29.86,29.86,0,0,1-8,1.65l5.88-63a3.79,3.79,0,0,0-.57-3.5A5.73,5.73,0,0,0,1031,447a6,6,0,0,0-7.21,3.13q-.66,3.6-1.37,9.86T1021,473.62q-.72,7.39-1.43,15.27t-1.23,14.7c0,.09,0,.17,0,.26a22.89,22.89,0,0,1-3.25,1.21,17,17,0,0,1-4.08.61,35.31,35.31,0,0,0,.62-3.79c.16-1.39.28-2.84.38-4.36s.12-3,.09-4.55-.11-2.91-.23-4.18a35.6,35.6,0,0,0-1.76-7.72,18.05,18.05,0,0,0-3.46-6.12,10.74,10.74,0,0,0-5.45-3.32,13.54,13.54,0,0,0-7.63.57,23,23,0,0,0-11.62,1.19,25.36,25.36,0,0,0-9,5.92,32.27,32.27,0,0,0-6.21,9.15,39.5,39.5,0,0,0-3.23,10.81,41.33,41.33,0,0,0-.37,4.69,27.5,27.5,0,0,1-3.23,5.22,28.15,28.15,0,0,1-5.21,5.12,23.8,23.8,0,0,1-5.36,3,26,26,0,0,1-4.74,1.42,13.3,13.3,0,0,1-4.74.09,7.84,7.84,0,0,1-4.17-2.18,8.49,8.49,0,0,1-2.33-4.26,29.79,29.79,0,0,1-.94-6.69,54.93,54.93,0,0,1,.28-7.82,44.28,44.28,0,0,1,1.47-7.73,30.81,30.81,0,0,1,2.65-6.54,10.32,10.32,0,0,1,3.8-4.13,1.72,1.72,0,0,1,1.51,1.47,10.47,10.47,0,0,1,.15,3c-.1,1.17-.24,2.37-.43,3.6a20.77,20.77,0,0,0-.28,3.08,7.51,7.51,0,0,0,1.84,4,5.21,5.21,0,0,0,3.09,1.66,4.93,4.93,0,0,0,3.36-.8,7.37,7.37,0,0,0,2.7-3.32.42.42,0,0,0,.29.09l1.33-12a5.24,5.24,0,0,0-.76-4.36,5,5,0,0,0-3.51-2.18,9.2,9.2,0,0,0-7.44-4.22,15.78,15.78,0,0,0-9.63,3.08,20.17,20.17,0,0,0-5.36,6,38.8,38.8,0,0,0-3.79,8.54,54.27,54.27,0,0,0-2.08,9.9,51.76,51.76,0,0,0-.24,10.15,41.45,41.45,0,0,0,1.75,9.29,21.17,21.17,0,0,0,3.84,7.3,12.89,12.89,0,0,0,4.74,3.75,17.81,17.81,0,0,0,5.55,1.47,20.45,20.45,0,0,0,5.74-.24,31.72,31.72,0,0,0,5.4-1.47,53,53,0,0,0,6.83-3.13,41.68,41.68,0,0,0,6.73-4.55,40.32,40.32,0,0,0,3.27-3,25.59,25.59,0,0,0,1.66,3.41,20.19,20.19,0,0,0,6.92,6.92,19.71,19.71,0,0,0,10.72,2.56A25.27,25.27,0,0,0,997.12,526a25.82,25.82,0,0,0,9.48-9.91,34,34,0,0,0,10.9-1.81c0,.38-.06.78-.09,1.15-.25,3.35-.38,5.62-.38,6.83-.06,2.08-.2,4.66-.43,7.72s-.36,6.29-.42,9.67a93,93,0,0,0,.38,10.25,37.68,37.68,0,0,0,2,9.38,20.07,20.07,0,0,0,4.31,7.16,11.83,11.83,0,0,0,7.35,3.51,11.62,11.62,0,0,0,8.35-1.71,17.68,17.68,0,0,0,5.69-6.49,31.67,31.67,0,0,0,3.08-9.53,46.47,46.47,0,0,0,.52-10.86,42,42,0,0,0-2-10.28,22.19,22.19,0,0,0-4.46-8,19.64,19.64,0,0,0,4.08-1.8c1.58-.89,3.2-1.88,4.88-3l1.23-.84c-.16,2.24-.23,3.84-.23,4.78-.07,2.08-.21,4.66-.43,7.72s-.36,6.29-.43,9.67a95.49,95.49,0,0,0,.38,10.25,38.14,38.14,0,0,0,2,9.38,20,20,0,0,0,4.32,7.16,11.78,11.78,0,0,0,7.35,3.51,11.6,11.6,0,0,0,8.34-1.71,17.59,17.59,0,0,0,5.69-6.49,31.39,31.39,0,0,0,3.08-9.53,46.47,46.47,0,0,0,.52-10.86,41.54,41.54,0,0,0-2-10.28,22,22,0,0,0-4.46-8,19.64,19.64,0,0,0,4.08-1.8c1.58-.89,3.21-1.88,4.89-3,.87-.57,1.73-1.17,2.59-1.78a24.4,24.4,0,0,0,2.14,8.09,15.71,15.71,0,0,0,5.55,6.45,16.47,16.47,0,0,0,8.25,2.51,27.06,27.06,0,0,0,10.34-1.76,28.34,28.34,0,0,0,7.25-3.79,27.53,27.53,0,0,0,5.55-5.55c.09-.12.18-.26.27-.39a20.52,20.52,0,0,0,1,2.53,15.76,15.76,0,0,0,5.54,6.45,16.47,16.47,0,0,0,8.25,2.51,27.06,27.06,0,0,0,10.34-1.76,28.34,28.34,0,0,0,7.25-3.79,27,27,0,0,0,5.55-5.55,44.07,44.07,0,0,0,4.5-7.54q2-4.26,4.13-9.76a2.8,2.8,0,0,0-.71-2.7M1137,497a46.22,46.22,0,0,1,.85-4.6,38,38,0,0,1,1.42-4.69,18.82,18.82,0,0,1,2-3.94,7.6,7.6,0,0,1,2.42-2.37,2.39,2.39,0,0,1,2.61.14c1,.57,1.53,1.77,1.75,3.61a13.78,13.78,0,0,1-.66,5.88,15.46,15.46,0,0,1-3.56,5.87,12.34,12.34,0,0,1-6.92,3.61,13.83,13.83,0,0,1,.1-3.51m-38.21,0a43.51,43.51,0,0,1,.85-4.6,38,38,0,0,1,1.42-4.69,18.35,18.35,0,0,1,2-3.94,7.6,7.6,0,0,1,2.42-2.37,2.39,2.39,0,0,1,2.61.14c.94.57,1.53,1.77,1.75,3.61a13.93,13.93,0,0,1-.66,5.88,15.59,15.59,0,0,1-3.56,5.87,12.34,12.34,0,0,1-6.92,3.61,13.38,13.38,0,0,1,.1-3.51m-104.92,18a16.91,16.91,0,0,1-3.27,2.7,15.2,15.2,0,0,1-3.7,1.71,7.24,7.24,0,0,1-3.42.28,10.73,10.73,0,0,1-6.54-3.7,14.08,14.08,0,0,1-2.89-6.68,24.94,24.94,0,0,1,.14-8.2,31,31,0,0,1,2.56-8.11,25.19,25.19,0,0,1,4.36-6.45,10.91,10.91,0,0,1,5.6-3.36,32.91,32.91,0,0,0-.76,10,28.08,28.08,0,0,0,2.47,9.72,25.26,25.26,0,0,0,3.17,5,17.18,17.18,0,0,0,4.51,3.89,12.38,12.38,0,0,1-2.23,3.18m8.39-18.92a27.83,27.83,0,0,1-.43,4,4,4,0,0,1-.9,2.23,9,9,0,0,1-2.56-2.94A20.24,20.24,0,0,1,996,494a15,15,0,0,1-.52-5.88,5.87,5.87,0,0,1,3-4.5,1.27,1.27,0,0,1,1.8.43,8.1,8.1,0,0,1,1.23,2.89,25.42,25.42,0,0,1,.66,4.36,40,40,0,0,1,.1,4.74m35.22,53.86a14.51,14.51,0,0,1-2.51,5.45,5.43,5.43,0,0,1-4.27,2.32,2.48,2.48,0,0,1-2.46-1.7,15,15,0,0,1-1.18-4.65,48.07,48.07,0,0,1-.29-6.35q0-3.51.29-6.92t.56-6.36c.22-2,.4-3.47.52-4.55a8.23,8.23,0,0,1,5.36,2.8,16.77,16.77,0,0,1,3.27,5.74,25.91,25.91,0,0,1,1.33,7.15,24,24,0,0,1-.62,7.07m34.33,0a14.83,14.83,0,0,1-2.51,5.45,5.43,5.43,0,0,1-4.27,2.32,2.48,2.48,0,0,1-2.47-1.7,15.25,15.25,0,0,1-1.18-4.65,49.84,49.84,0,0,1-.29-6.35c0-2.34.13-4.65.29-6.92s.35-4.4.57-6.36.39-3.47.52-4.55a8.23,8.23,0,0,1,5.36,2.8,16.77,16.77,0,0,1,3.27,5.74,25.91,25.91,0,0,1,1.33,7.15,24.31,24.31,0,0,1-.62,7.07" style="fill:none;clip-rule:evenodd"/></clipPath></defs><g style="clip-path:url(#a)"><g style="clip-path:url(#b)"><rect x="163.06" y="3.17" width="35.47" height="35.47" style="fill:#fd0"/></g></g><g style="clip-path:url(#c)"><g style="clip-path:url(#b)"><rect x="60.49" y="29.3" width="96.54" height="133.05" style="fill:#ff9100"/></g></g><g style="clip-path:url(#e)"><g style="clip-path:url(#b)"><rect x="60.49" y="29.3" width="86.84" height="133.05" style="fill:#fd0"/></g></g><g style="clip-path:url(#g)"><g style="clip-path:url(#b)"><rect x="49.4" y="18.14" width="112.13" height="23.19" style="fill:#fff"/></g></g><path d="M436,437.45H330.75V421.1H436Zm-100.1-5.19h94.9v-6h-94.9Z" transform="translate(-277.93 -399.55)"/><g style="clip-path:url(#i)"><g style="clip-path:url(#b)"><rect x="60.83" width="88.57" height="28.77" style="fill:#fff"/></g></g><path d="M425.28,424.9H340.81L350.34,403h65.41Zm-76.55-5.2h68.63l-5-11.54H353.75Z" transform="translate(-277.93 -399.55)" style="fill:#050505"/><path d="M412.11,558.47H354.33L334.46,432.24l48.76.25,48.76-.25Zm-53.34-5.19h48.9L425.9,437.47l-42.69.22-42.67-.22Z" transform="translate(-277.93 -399.55)"/><g style="clip-path:url(#k)"><g style="clip-path:url(#b)"><rect x="51.83" y="63.47" width="106.58" height="60.16" style="fill:#fff"/></g></g><path d="M424,519.79,383,519.34l-40.89.45-9.46-53.35H433.42ZM383,514.15l36.59.39,7.61-42.91H338.87l7.61,42.91Z" transform="translate(-277.93 -399.55)"/><g style="clip-path:url(#m)"><g style="clip-path:url(#b)"><path d="M300.53,474a22.6,22.6,0,1,1,22.6-22.6A22.62,22.62,0,0,1,300.53,474Zm0-28.46a5.86,5.86,0,1,0,5.86,5.86A5.87,5.87,0,0,0,300.53,445.56Z" transform="translate(-277.93 -399.55)" style="fill:#eee"/></g></g><g style="clip-path:url(#o)"><g style="clip-path:url(#b)"><rect x="158.04" y="81.85" width="25.42" height="25.42" style="fill:#eee"/></g></g><g style="clip-path:url(#q)"><g style="clip-path:url(#b)"><rect x="32.49" y="120.36" width="25.42" height="25.42" style="fill:#ff813f"/></g></g><g style="clip-path:url(#s)"><g style="clip-path:url(#b)"><rect x="199.64" y="40.73" width="69.23" height="95.01"/></g></g><g style="clip-path:url(#u)"><g style="clip-path:url(#b)"><rect x="258.23" y="66.48" width="134.95" height="114"/></g></g><g style="clip-path:url(#w)"><g style="clip-path:url(#b)"><rect x="398.17" y="64.02" width="149.25" height="76.07"/></g></g><g style="clip-path:url(#y)"><g style="clip-path:url(#b)"><rect x="552.93" y="66.4" width="79.16" height="71.34"/></g></g><g style="clip-path:url(#aa)"><g style="clip-path:url(#b)"><rect x="637.27" y="41.16" width="264.11" height="135.42"/></g></g></svg>
            </a>
          </div>
        </div>
      </div>
    </transition>
  </main>
</template>

<script>
export default {
  name: 'App',

  data() {
    return {
      loading: true,
      uploading: false,
      progress: 0,
      OTAError: null,
      OTASuccess: false,

      type: 'firmware',
      files: null,
      deviceData: {
        id: null,
        hardware: null,
      },
    };
  },

  methods: {
    uploadOTA() {
      this.uploading = true;
      const formData = new FormData();
      formData.append(this.type, this.$refs.file.files[0]);
      const request = new XMLHttpRequest();

      request.addEventListener('load', () => {
        // request.response will hold the response from the server
        if (request.status === 200) {
          this.OTASuccess = true;
        } else if (request.status !== 500) {
          this.OTAError = `[HTTP ERROR] ${request.statusText}`;
        } else {
          this.OTAError = request.responseText;
        }
        this.uploading = false;
        this.progress = 0;
      });

      // Upload progress
      request.upload.addEventListener('progress', (e) => {
        this.progress = Math.trunc((e.loaded / e.total) * 100);
      });

      request.withCredentials = true;
      request.open('post', '/update');
      request.send(formData);
    },

    retryOTA() {
      this.OTAError = null;
      this.OTASuccess = false;
      this.uploadOTA();
    },

    clear() {
      this.OTAError = null;
      this.OTASuccess = false;
    },
  },

  mounted() {
    fetch('/update/identity').then(async (response) => {
      if (response.ok) {
        this.deviceData = await response.json();
        this.loading = false;
      }
    }).catch(() => {

    });
  },

};
</script>

<style lang="scss">
$primary-color: #488EFF;
// Variables and mixins
@import "~spectre.css/src/variables";
@import "~spectre.css/src/mixins";

/*! Spectre.css v#{$version} | MIT License | github.com/picturepan2/spectre */
// Reset and dependencies
@import "~spectre.css/src/normalize";
@import "~spectre.css/src/base";

// Elements
@import "~spectre.css/src/typography";

@import "~spectre.css/src/labels";
@import "~spectre.css/src/buttons";
@import "~spectre.css/src/tooltips";
@import "~spectre.css/src/cards";
@import "~spectre.css/src/bars";
@import "~spectre.css/src/forms";

@import "~spectre.css/src/layout";

@import "~spectre.css/src/animations";
@import "~spectre.css/src/utilities";

.logo{
  width: 100%;
  max-width: 320px;
}

.card{
  border: 0;
  box-shadow: 0 0.25rem 1rem rgba(48,55,66,.1);
  border-radius: 0.275rem;
}

.label{
  font-size: 0.65rem !important;
}

.file-input{
  border-radius: 0.275rem;
}

.shape{
  position: absolute;
  top: 0;
  right: 0;
  bottom: auto;
  width: 300px;
  opacity: 0.4;
  overflow: hidden;
  z-index: 0;

  @media only screen and (min-width: 425px) {
    width: 140px;
    bottom: 0;
    top: auto;
  }

  @media only screen and (min-width: 768px) {
    width: 240px;
    bottom: auto;
    top: 0;
  }
}

.shape>svg{
  fill: rgba(72,142,255, 0.05);
  transform: scaleY(-1);
}

.coffee-link{
  position: absolute;
  bottom: 0;
  left: 0;
  margin: 1rem;
  .card{
    box-shadow: none;
  }
}

.pt-3{
  padding-top: 32px;
}

.mt-3{
  margin-top: 24px;
}

.fade-enter-active, .fade-leave-active {
  transition: opacity .25s;
}
.fade-enter, .fade-leave-to /* .fade-leave-active below version 2.1.8 */ {
  opacity: 0;
}

.slide-fade-enter-active {
  transition: all .8s ease;
}
.slide-fade-leave-active {
  transition: all .8s cubic-bezier(1.0, 0.5, 0.8, 1.0);
}
.slide-fade-enter, .slide-fade-leave-to {
  transform: translateY(120px);
  opacity: 1;
}
</style>
