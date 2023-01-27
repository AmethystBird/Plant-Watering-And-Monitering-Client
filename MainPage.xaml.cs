//using Android.Content.Res;

using LiveChartsCore.SkiaSharpView;
using LiveChartsCore;
using System.Collections.ObjectModel;

namespace PlantWateringAndMonitoringSystem;
public partial class MainPage : ContentPage
{
    float lightValue;
	float moistureValue;
	float temperatureValue;
	float humidityValue;
    SensorGraph testSensorGraph;
    public MainPage()
	{
		InitializeComponent();

		lightValue = 0.0f;
		moistureValue = 1.0f;
		temperatureValue = 2.0f;
		humidityValue = 4.0f;

        testSensorGraph = new SensorGraph();
        BindingContext = testSensorGraph.Series;
    }
	async void OnSensorButtonClicked(object sender, EventArgs e)
	{
        Button button = (Button)sender;
        if (button.Text == "Light")
        {
			ChangeSensorToDisplay(lightValue.ToString(), " lux");
        }
        if (button.Text == "Moisture")
        {
            ChangeSensorToDisplay(moistureValue.ToString(), "%");
        }
        if (button.Text == "Temperature")
        {
            ChangeSensorToDisplay(temperatureValue.ToString(), " *C");
        }
        if (button.Text == "Humidity")
        {
            ChangeSensorToDisplay(humidityValue.ToString(), " <humidityLvl>");
        }
    }
    async void OnButtonPressed(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        button.BorderColor = Colors.White;
    }
    async void OnButtonReleased(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        button.BorderColor = Colors.Black;
    }
    void ChangeSensorToDisplay(string valueDisplay, string measurementSuffix)
	{
		Resources["valueLabel"] = valueDisplay + measurementSuffix;
    }
    //override 
    /*private void OnCounterClicked(object sender, EventArgs e)
	{
		count++;

		if (count == 1)
			CounterBtn.Text = $"Clicked {count} time";
		else
			CounterBtn.Text = $"Clicked {count} times";

		SemanticScreenReader.Announce(CounterBtn.Text);
	}*/
}

