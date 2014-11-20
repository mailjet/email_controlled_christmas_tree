class ChangeLightsController < ApplicationController
   protect_from_forgery with: :null_session, if: Proc.new { |c| c.request.format == 'application/json' }
   def email_received
      led_pattern = params["Subject"].downcase #downcase for logic
      HTTParty.post("https://api.spark.io/v1/devices/#{ENV['coreID']}/led_strip", body: {access_token: ENV['accessToken'], led_pattern: led_pattern})
   end
end
