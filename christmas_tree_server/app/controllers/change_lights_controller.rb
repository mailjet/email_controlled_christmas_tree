class ChangeLightsController < ApplicationController
   protect_from_forgery with: :null_session, if: Proc.new { |c| c.request.format == 'application/json' }
   def email_received
     words = params["Text-part"].split(" ")
     led_pattern = words[(words.index("strip")+1)].downcase unless words.index("strip").nil?
     matrix_contents = words[(words.index("matrix")+1)].downcase unless words.index("matrix").nil?
     background = words[(words.index("background")+1)].downcase unless words.index("background").nil?

     #POST request for LED strip
     unless led_pattern.nil?
        HTTParty.post("https://api.spark.io/v1/devices/#{ENV['coreID']}/led_strip", body: {access_token: ENV['accessToken'], led_pattern: led_pattern})
      end

      #POST request for LED background color
      unless background.nil?
        # matrix_contents = format_matrix_contents(params["Text-part"])
        HTTParty.post("https://api.spark.io/v1/devices/#{ENV['coreID']}/background", body: {access_token: ENV['accessToken'], background: background})
      end

      #POST request for LED dot matrix
      unless matrix_contents.nil?
        # matrix_contents = format_matrix_contents(params["Text-part"])
        HTTParty.post("https://api.spark.io/v1/devices/#{ENV['coreID']}/dot_matrix", body: {access_token: ENV['accessToken'], matrix_contents: matrix_contents})
      end
   end

   private
   def format_matrix_contents(text)

   end
end
