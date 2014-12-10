class ChangeLightsController < ApplicationController
   protect_from_forgery with: :null_session, if: Proc.new { |c| c.request.format == 'application/json' }
   def email_received
     words = params["Text-part"].split(" ")
     lights = words[(words.index("lights")+1)].downcase unless words.index("lights").nil?
     icon = words[(words.index("icon")+1)].downcase unless words.index("icon").nil?
     background = words[(words.index("background")+1)].downcase unless words.index("background").nil?

     #POST request for LED strip
     unless lights.nil?
        HTTParty.post("https://api.spark.io/v1/devices/#{ENV['coreID']}/led_strip", body: {access_token: ENV['accessToken'], lights: lights})
      end

      #POST request for LED background color
      unless background.nil?
        # icon = format_icon(params["Text-part"])
        HTTParty.post("https://api.spark.io/v1/devices/#{ENV['coreID']}/background", body: {access_token: ENV['accessToken'], background: background})
      end

      #POST request for LED dot matrix
      unless icon.nil?
        # icon = format_icon(params["Text-part"])
        HTTParty.post("https://api.spark.io/v1/devices/#{ENV['coreID']}/dot_matrix", body: {access_token: ENV['accessToken'], icon: icon})
      end
   end

   private
   def format_icon(text)

   end
end
