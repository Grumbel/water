;; Simple Water Wave Effect in OpenGL
;; Copyright (C) 2004 Ingo Ruhnke <grumbel@gmail.com>
;;
;; This program is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.

(set! %load-path
  (cons* "/ipfs/QmdrwuaArAXmKGPY3oEoNpxTp7EUSKetXAVGBt67nqo54X/guix-cocfree_0.0.0-59-gd79b2bf"
         %load-path))

(use-modules (guix build-system cmake)
             ((guix licenses) #:prefix license:)
             (guix packages)
             (gnu packages gl)
             (gnu packages pkg-config)
             (guix-cocfree utils))

(define %source-dir (dirname (current-filename)))

(define-public water-fx
  (package
   (name "water-fx")
   (version (version-from-source %source-dir))
   (source (source-from-source %source-dir))
   (build-system cmake-build-system)
   (arguments
    `(#:tests? #f))
   (native-inputs
    `(("pkg-config" ,pkg-config)))
   (inputs
    `(("freeglut" ,freeglut)
      ("mesa" ,mesa)
      ("glu" ,glu)))
   (synopsis "Simple Water Wave Effect in OpenGL")
   (description (description-from-source %source-dir))
   (home-page (homepage-from-source %source-dir))
   (license license:gpl3)))

water-fx

;; EOF ;;
