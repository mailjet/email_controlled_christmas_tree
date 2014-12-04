# Email Controlled Christmas Tree

![RGB Dot Matrix](https://raw.githubusercontent.com/tylernappy/email_controlled_christmas_tree/master/assets/images/dot_matrix.jpg "Text")

### Overview
Using [Mailjet's](https://www.mailjet.com/) [Parse API](http://dev.mailjet.com/guides/parse-api-guide/) -- easy way to receive content of an email to your webhook -- and a simple Rails server to receive and process incoming emails, LEDs and ornaments, hooked up to a [Spark Core](https://www.spark.io/dev-kits) microcontroller, are controlled using commands sent via email.  Simply send an email to the email address returned when creating an instance of the Parse API with the color scheme of LEDs, the background of the LED dot matrix (aka the star on top of the tree), and what to display on the LED dot matrix (a star, a smiley face, some writing) and all of these will be updated instantly.

### Layout of files in this repo
* **christmas_tree_server**
 * Rails app that receives POST request from Mailjet's Parse API of the email contents of the email sent.  It then performs preliminary formating and logic before sending this information to the Spark Core via a POST request.
 * POST request from Mailjet is done to '/email_processor'.  This then dumps the content of the received email in the params to the controller method 'email_received'.  To update any logic here, navigate to the controller found [here](https://github.com/tylernappy/email_controlled_christmas_tree/blob/master/christmas_tree_server/app/controllers/change_lights_controller.rb) - `email_controlled_christmas_tree/christmas_tree_server/app/controllers/change_lights_controller.rb`
* **tree.ino**
  * Spark Core file that controls LEDs and LED dot matrix.  Receives POST requests from Rails app and changes the LEDs and LED dot matrix based on the commands sent.

### Hardware used
* 1 2ft Christmas tree (obviously)
* 1 [Spark Core](https://www.adafruit.com/products/2127)
* 2 meters of [Adafruit NeoPixel Digital RGB LED Strip - White 30 LED](https://www.adafruit.com/products/1376) (length will change depending on size of tree -- see this [app]() to estimate how much is required for your tree)
* 1 LED dot matrix ([Medium 16x32 RGB LED matrix panel](https://www.adafruit.com/products/420))
* 1 [5V 10A switching power supply](http://www.adafruit.com/products/658)
* 1 [Female DC Power adapter - 2.1mm jack to screw terminal block](http://www.adafruit.com/products/368)
* 1 ["Mini"ish screwdriver](https://raw.githubusercontent.com/tylernappy/email_controlled_christmas_tree/master/assets/images/mini_screwdriver.jpg "Text")
* 1 [4700uF 10v Electrolytic Capacitor](http://www.adafruit.com/products/1589)
* 1 [USB A/Micro B](http://www.adafruit.com/products/898) (one comes with the Spark Core)
* Many [jumper wires](http://www.adafruit.com/products/758)

### Software and libraries used
* Spark Core
 * [SparkCore-NeoPixel](https://github.com/technobly/SparkCore-NeoPixel)
 * [SparkIntervalTimer](https://github.com/pkourany/SparkIntervalTimer)
 * [Adafruit_mfGFX Library](https://github.com/pkourany/Adafruit_mfGFX_IDE)
 * [RGB Matrix Panel](https://github.com/pkourany/RGBmatrixPanel_IDE)
* Rails
 * [ngrok](https://ngrok.com/) -- very awesome for testing webhooks
 * [Mailjet ruby wrapper](https://github.com/mailjet/mailjet-gem)
 * [HTTParty](https://github.com/jnunemaker/httparty)

### Setup
1. Setup and wire Spark Core to LEDs and LED dot matrix.  Check out [this]() blog post for wiring instructions
2. Clone this repository to your computer - `git clone https://github.com/tylernappy/email_controlled_christmas_tree.git`
3. Upload `tree.ino` to Spark Core (their [browser IDE](https://www.spark.io/build) is very good for doing this -- make a new app, copy and paste the code in `tree.ino` into the IDE, click 'Flash' to upload to core)
4. `cd` into `christmas_tree_server`
5. Run `bundle`
6. Update environment variables for your Mailjet API Key and Secret Key, and Spark Core ID and Access Token
7. Run a `rails server`
8. Run ngrok on port 3000 -- `./ngrok 3000`
 * It will display a URL where you can access your server.  Use this in step 11.
9. Create a [Mailjet](https://www.mailjet.com/signup) account
10. Find your Mailjet API Key and Secret Key [here](https://app.mailjet.com/account/setup)
11. Setup instance of [Parse API](http://dev.mailjet.com/guides/parse-api-guide/) by using the following curl request.   Remember to use the URL returned when you ran ngrok.  It will return back to you the email address people will send to to update the LEDs and LED dot matrix on the christmas tree:
 * ```curl --user "API_KEY:SECRET_KEY" https://api.mailjet.com/v3/REST/parseroute -H 'Content-Type: application/json' -d '{"Url":"http://your.webhook.com/email_processor"}'```
12. Start emailing to control the christmas tree!

### Commands to update the Christmas tree
Commands are sent via email to the email address returned to you when creating an instance of Mailjet's Parse API.  Three commands are allowed -- update the LEDs on the tree, update the background of the LED dot matrix, and update image/writing on the LED dot matrix.  You do not need to include all three for this to work.  For example, you can update only the LEDs while keeping the LED dot matrix background and image the same.

* Command to update LEDs --> `strip`
* Command to update LED dot matrix background --> `background`
* Command to update LED dot matrix image --> `matrix`

Commands are written in the body of the email by specifying the action (changing the LEDs, changing the background and image on LED dot matrix) followed by what you'd like to change it to.   Commands can be sent in no particular order.  Here are example calls:

* Blue LEDs; Red dot matrix background; Star as shape on dot matrix
 * `strip blue background red matrix star`
* Christmas colors LEDs; green dot matrix background; Mailjet logo as shape on dot matrix
 * `strip christmas background green matrix mailjet`
* Green LEDs; blank background on dot matrix background; Circle as shape on dot matrix
 * `strip green background blank matrix circle`

Here is a list of all commands currently available for each variable:
* LEDs - `strip`
  * `blue`
  * `green`
  * `red`
  * `christmas`
  * `mailjet`
* LED dot matrix background - `background`
 * `blue`
 * `red`
 * `green`
 * `blank`
 * `nothing`
 * `black`
* LED dot matrix image - `matrix`
 * `circle`
 * `mailjet`
 * `star`
 * `logo`

### Adding updates
Fork the repo, make changes, and submit a pull request.  Also, would love to hear your feedback!  Email us at [api@mailjet.com]().
